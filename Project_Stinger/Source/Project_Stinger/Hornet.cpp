#include "Hornet.h"

#include "Octree.h"
#include "StingerGameMode.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AHornet::AHornet()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(FName("Sphere Collider"));
	SphereCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SphereCollider->SetSphereRadius(100);
	SphereCollider->SetMobility(EComponentMobility::Movable);
	SetRootComponent(SphereCollider);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Mesh"));
	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	Arrow = CreateDefaultSubobject<UArrowComponent>(FName("Forward Arrow"));
	Arrow->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Arrow->ArrowSize = 1.5;
	Arrow->ArrowLength = 100;
}

void AHornet::BeginPlay()
{
	Super::BeginPlay();

	Transform = GetActorTransform();

	if (AStingerGameMode* GameMode = Cast<AStingerGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
		GameMode->HornetSpawned(this);
}

void AHornet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentMoveVector = NewMoveVector;

	UpdateNeighbourhood();

	CalculateNewMoveVector();

	UpdateTransform(DeltaTime);

	// Debug
	DrawDebug();
}


void AHornet::CalculateNewMoveVector()
{
	ResetForces();

	CalculateAlignment();

	if (Neighborhood.Num() > 0)
	{
		CalculateCohesion();
		CalculateSeparation();
	}
	else
	{
		//CalculateRandomMoveVector();
	}

	CalculateCollisions();

	NewMoveVector += AlignmentForce + CohesionForce + SeparationForce + CollisionForce;
}

void AHornet::ResetForces()
{
	CohesionForce = FVector::Zero();
	AlignmentForce = FVector::Zero();
	SeparationForce = FVector::Zero();
	NewMoveVector = FVector::Zero();
}

void AHornet::CalculateAlignment()
{
	for (const AHornet* Neighbor : Neighborhood)
	{
		if (Neighbor && GetDistanceTo(Neighbor) < AlignmentRadius)
		{
			AlignmentForce += Neighbor->CurrentMoveVector.GetSafeNormal();
		}
	}

	AlignmentForce = (CurrentMoveVector + AlignmentForce).GetSafeNormal() * AlignmentWeight;
}

void AHornet::CalculateCohesion()
{
	const FVector& Location = GetActorLocation();
	for (const AHornet* Neighbor : Neighborhood)
	{
		if(Neighbor && GetDistanceTo(Neighbor) < CohesionRadius)
		{
			CohesionForce += Neighbor->GetActorLocation() - Location;
		}
	}

	CohesionForce = (CohesionForce / Neighborhood.Num()).GetSafeNormal() * CohesionWeight;
}

void AHornet::CalculateSeparation()
{
	const FVector& Location = GetActorLocation();
	for (const AHornet* Neighbor : Neighborhood)
	{
		if(Neighbor && GetDistanceTo(Neighbor) < SeparationRadius)
		{
			// The agent will move away from neighbors inversely proportionally to the distance between them.
			FVector Direction = Location - Neighbor->GetActorLocation();
			float Distance = Direction.Size();

			SeparationForce += Direction.GetUnsafeNormal() / Distance;
		}
	}

	// TODO: Clamp Separation Force
	SeparationForce = SeparationForce.GetSafeNormal() * SeparationWeight * SeparationWeightScale;
}

void AHornet::CalculateCollisions()
{
	CollisionForce = FVector::Zero();
}

void AHornet::CalculateRandomMoveVector()
{
	float RandomX = FMath::FRandRange(-1.0f, 1.0f);
	float RandomY = FMath::FRandRange(-1.0f, 1.0f);
	float RandomZ = FMath::FRandRange(-1.0f, 1.0f);

	// Normalize the vector to get a unit vector
	FVector RandomVector = FVector(RandomX, RandomY, RandomZ).GetSafeNormal();

	// Scale the vector based on the desired speed range
	float RandomSpeed = FMath::FRandRange(MoveSpeed, MaxSpeed);
	NewMoveVector = RandomVector * RandomSpeed;
}

void AHornet::UpdateNeighbourhood()
{
	if(!HornetOctree) return;

	Neighborhood.Empty();
	HornetOctree->GetNeighbors(Neighborhood, this);
}

void AHornet::UpdateTransform(float DeltaTime)
{
	const FVector NewDirection = (NewMoveVector * MoveSpeed * DeltaTime).GetClampedToMaxSize(MaxSpeed * DeltaTime);
	Transform.SetLocation(Transform.GetLocation() + NewDirection);
	Transform.SetRotation(UKismetMathLibrary::RLerp(Transform.Rotator(),UKismetMathLibrary::MakeRotFromXZ(NewDirection, FVector::UpVector),DeltaTime * MaxRotationSpeed, false).Quaternion());
	SetActorTransform(Transform);
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
	// DrawDebugSphere(World, Location, VisionRadius, 10, FColor::Red, false, -1, 1, 1);

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
	/*for (const auto Hornet : Neighborhood)
	{
		DrawDebugLine(World, Location, Hornet->GetActorLocation(), FColor::Yellow, false, -1, 0, 1.5f);
	}*/
}