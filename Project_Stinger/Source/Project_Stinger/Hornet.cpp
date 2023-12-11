#include "Hornet.h"

#include "StingerGameMode.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AHornet::AHornet()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(FName("Sphere Collider"));
	SphereCollider->SetSphereRadius(100);
	SphereCollider->SetMobility(EComponentMobility::Movable);
	SetRootComponent(SphereCollider);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

void AHornet::BeginPlay()
{
	Super::BeginPlay();

	Transform = GetActorTransform();

	HornetController = Cast<AHornetController>(GetController());
	if (HornetController)
	{
		HornetController->ActionChangedEvent.AddDynamic(this, &AHornet::OnHornetActionUpdated);
		HornetController->StateChangedEvent.AddDynamic(this, &AHornet::OnHornetStateUpdated);
	}

	if (AStingerGameMode* GameMode = Cast<AStingerGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
		GameMode->HornetSpawned(this);

	ActionFunctionMap.Add(Wandering, &AHornet::Wander);
	ActionFunctionMap.Add(Swarming, &AHornet::Swarm);
	ActionFunctionMap.Add(Charging, &AHornet::Charge);
	ActionFunctionMap.Add(Chasing, &AHornet::Chase);
	ActionFunctionMap.Add(Fleeing, &AHornet::Flee);

	CurrentAction = Wandering;

	MaxSpeed += UKismetMathLibrary::RandomFloatInRange(-1 * MaxSpeedVariance, MaxSpeedVariance);
	NewMoveVector = UKismetMathLibrary::RandomUnitVector() * MaxSpeed;
}

void AHornet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!HasAuthority()) return;

	CurrentMoveVector = NewMoveVector;

	if(ActionFunctionMap.Contains(CurrentAction))
		(this->**ActionFunctionMap.Find(CurrentAction))();

	UpdateTransform(DeltaTime);

	// Debug
	DrawDebug();
}


void AHornet::CalculateNewMoveVector()
{
	ResetForces();

	//GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Cyan, FString::Printf(TEXT("%f"), Neighborhood.Num()));
	if (Neighborhood.Num() > 0)
	{
		CalculateAlignment();
		CalculateCohesion();
		CalculateSeparation();
	}

	CalculateVariance();
	AvoidanceForce = HornetController->CalculateAvoidanceDirection();
	
	NewMoveVector += 
		AlignmentForce.GetSafeNormal() * AlignmentWeight + 
		CohesionForce * CohesionWeight + 
		SeparationForce * SeparationWeight + 
		VarianceForce * VarianceWeight +
		CurrentMoveVector.GetSafeNormal() * ResistanceToChange +
		AvoidanceForce * AvoidanceWeight;
}

void AHornet::ResetForces()
{
	CohesionForce = FVector::Zero();
	AlignmentForce = FVector::Zero();
	SeparationForce = FVector::Zero();
	AvoidanceForce = FVector::Zero();
	NewMoveVector = FVector::Zero();
}

void AHornet::CalculateAlignment()
{
	AlignmentForce = CurrentMoveVector;
	int ValidNeighbors = 1;
	for (const AHornet* Neighbor : Neighborhood)
	{
		if (Neighbor && GetDistanceTo(Neighbor) < AlignmentRadius)
		{
			ValidNeighbors++;
			AlignmentForce += Neighbor->CurrentMoveVector;
		}
	}

	AlignmentForce /= ValidNeighbors;
}

void AHornet::CalculateCohesion()
{
	const FVector& Location = GetActorLocation();
	FVector CenterMass = Location;

	int ValidNeighbors = 1;

	for (const AHornet* Neighbor : Neighborhood)
	{
		if(Neighbor && GetDistanceTo(Neighbor) < CohesionRadius)
		{
			ValidNeighbors++;
			CenterMass += Neighbor->GetActorLocation();
		}
	}

	CenterMass /= ValidNeighbors;

	FVector dir = CenterMass - Location;

	CohesionForce = (dir / CohesionRadius);
}

void AHornet::CalculateSeparation()
{
	const FVector& Location = GetActorLocation();
	for (const AHornet* Neighbor : Neighborhood)
	{
		if(Neighbor && GetDistanceTo(Neighbor) < SeparationRadius)
		{
			// The agent will move away from neighbors inversely proportionally to the distance between them.
			FVector Vector = Location - Neighbor->GetActorLocation();
			
			SeparationForce += Vector / Vector.SquaredLength();
		}
	}
}

void AHornet::CalculateVariance() 
{
	VarianceForce = UKismetMathLibrary::RandomUnitVector();
}

void AHornet::UpdateTransform(float DeltaTime)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Cyan, FString::Printf(TEXT("%f, %f, %f"), NewMoveVector.X, NewMoveVector.Y, NewMoveVector.Z));
	const FVector NewDirection = (NewMoveVector * MoveSpeed * DeltaTime).GetClampedToMaxSize(MaxSpeed * DeltaTime);
	Transform.SetLocation(Transform.GetLocation() + NewDirection);
	Transform.SetRotation(UKismetMathLibrary::RLerp(Transform.Rotator(),UKismetMathLibrary::MakeRotFromXZ(NewDirection, FVector::UpVector),DeltaTime * MaxRotationSpeed, false).Quaternion());
	SetActorTransform(Transform);
}

void AHornet::Wander()
{
	//CalculateNewMoveVector();
}

void AHornet::Swarm()
{
	CalculateNewMoveVector();
}

void AHornet::Charge()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Cyan, FString::Printf(TEXT("Charge")));
}

void AHornet::Chase()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Cyan, FString::Printf(TEXT("Chase")));
}

void AHornet::Flee()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Cyan, FString::Printf(TEXT("Flee")));
}

/**
 *	Combat Behavior 
 */

void AHornet::Hit()
{
	IBulletHitInterface::Hit();

	Destroy();
}

void AHornet::Destroyed()
{
	Super::Destroyed();

	if (AStingerGameMode* GameMode = Cast<AStingerGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
		GameMode->HornetDestroyed(this);
}

/**
 *	Debugging
 */

void AHornet::DrawDebug() const
{
	const UWorld* World = GetWorld();
	const FVector& Location = GetActorLocation();

	// Sight Radius
	// DrawDebugSphere(World, Location, VisionRadius, 10, FColor::Blue, false, -1, 1, 1);

	// Movement Vector
	// DrawDebugLine(World, Location, Location + CurrentMoveVector.GetSafeNormal() * MoveSpeed, FColor::Green, false, -1, 1, 1.5f);

	// Alignment Radius
	// DrawDebugSphere(World, Location, AlignmentRadius, 10, FColor::Green, false, -1, 0, 1);

	// Alignment Radius
	// TODO: Finish

	// Cohesion Radius
	// DrawDebugSphere(World, Location, CohesionRadius, 10, FColor::Orange, false, -1, 0, 1);

	// Cohesion Vector
	// DrawDebugLine(World, Location,Location + CohesionForce.GetSafeNormal() * CohesionWeight * 50, FColor::Orange, false, -1, 0, 1.5f);

	// Separation Radius
	// DrawDebugSphere(World, Location, SeparationRadius, 10, FColor::Blue, false, -1, 0, 1);

	// Separation Vector
	// DrawDebugLine(World, Location,Location + SeparationForce.GetSafeNormal() * SeparationWeight * 50, FColor::Blue, false, -1, 0, 1.5f);

	//Draw Connections to Neighbors
	//for (const auto Hornet : Neighborhood)
	//{
	//	DrawDebugLine(World, Location, Hornet->GetActorLocation(), FColor::Yellow, false, -1, 0, 1.5f);
	//}
}