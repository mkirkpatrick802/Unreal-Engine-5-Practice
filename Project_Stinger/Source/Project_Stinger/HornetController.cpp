#include "HornetController.h"

#include "Hornet.h"
#include "Octree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AHornetController::AHornetController()
{
	PrimaryActorTick.bCanEverTick = true;

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception"));
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AHornetController::OnPawnDetected);

	// Create and configure sight sense
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SightConfig->SightRadius = 1000.f;
	SightConfig->LoseSightRadius = 1200.f;
	SightConfig->PeripheralVisionAngleDegrees = 50.f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;  
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->AutoSuccessRangeFromLastSeenLocation = -1.f;
	SightConfig->PointOfViewBackwardOffset = 200.f;
	SightConfig->NearClippingRadius = 200.f;

	// Register the sight sense
	AIPerceptionComponent->ConfigureSense(*SightConfig);
}

void AHornetController::BeginPlay()
{
	Super::BeginPlay();

	Hornet = Cast<AHornet>(GetPawn());
	CurrentAction = Wandering;

	HornetOctree->GetBounds(OctreeBoundsMin, OctreeBoundsMax);
}

void AHornetController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!HasAuthority()) return;

	/*if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		EnhancedInputComponent->BindAction(ToggleFlockStateAction, ETriggerEvent::Started, this, &AHornetController::ToggleFlockState);
	}*/

	UpdateNeighbourhood();
	//UpdateFlock();
}

FVector AHornetController::CalculateAvoidanceDirection()
{
	FVector ActorPosition = Hornet->GetActorLocation();

	ActorPosition.X = FMath::Clamp(ActorPosition.X, OctreeBoundsMin.X, OctreeBoundsMax.X);
	ActorPosition.Y = FMath::Clamp(ActorPosition.Y, OctreeBoundsMin.Y, OctreeBoundsMax.Y);
	ActorPosition.Z = FMath::Clamp(ActorPosition.Z, OctreeBoundsMin.Z, OctreeBoundsMax.Z);

	FVector AvoidanceVector = FVector::ZeroVector;

	if (ActorPosition.X == OctreeBoundsMin.X || ActorPosition.X == OctreeBoundsMax.X)
	{
		AvoidanceVector.X = -FMath::Sign(ActorPosition.X - (OctreeBoundsMin.X + OctreeBoundsMax.X) * 0.5f);
	}

	if (ActorPosition.Y == OctreeBoundsMin.Y || ActorPosition.Y == OctreeBoundsMax.Y)
	{
		AvoidanceVector.Y = -FMath::Sign(ActorPosition.Y - (OctreeBoundsMin.Y + OctreeBoundsMax.Y) * 0.5f);
	}

	if (ActorPosition.Z == OctreeBoundsMin.Z || ActorPosition.Z == OctreeBoundsMax.Z)
	{
		AvoidanceVector.Z = -FMath::Sign(ActorPosition.Z - (OctreeBoundsMin.Z + OctreeBoundsMax.Z) * 0.5f);
	}

	FVector RayStart = ActorPosition;
	FVector RayEnd = ActorPosition + Hornet->GetActorForwardVector() * 100;

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, RayStart, RayEnd, ECC_Visibility, CollisionParams))
		AvoidanceVector += HitResult.ImpactNormal;

	AvoidanceVector.Normalize();

	return AvoidanceVector;
}

void AHornetController::ChangeAction(HornetActions NewAction)
{
	if(NewAction == CurrentAction) return;
	CurrentAction = NewAction;

	if(CurrentState == Soldier)
	{
		if (CurrentAction == Swarming)
			CurrentAction = Flocking;

		if (CurrentAction == Chasing)
			CurrentAction = Charging;

		//if (CurrentAction == Fleeing)
		//	CurrentAction = Retreating;
	}

	ActionChangedEvent.Broadcast(CurrentAction);
}

void AHornetController::OnPawnDetected(AActor* Actor, FAIStimulus Stimulus)
{

}

void AHornetController::UpdateNeighbourhood()
{
	if (!HornetOctree || !Hornet) return;

	Neighborhood.Empty();
	HornetOctree->GetNeighbors(Neighborhood, Hornet);
	Hornet->SetNeighborhood(Neighborhood);

	ChangeAction(Neighborhood.Num() > 0 ? Swarming : Wandering);
}

void AHornetController::UpdateFlock()
{
	if (!HornetOctree || !Hornet) return;

	Flock.Empty();
	for (auto DirectHornet : Neighborhood)
	{
		TArray<AHornet*> Neighbors;
		DirectHornet->GetNeighborhood(Neighbors);
		for (auto AnotherHornet : Neighbors)
		{
			Flock.AddUnique(AnotherHornet);
		}
	}
}

void AHornetController::CalculateFlockForce()
{
	if(CurrentAction == Wandering) return;

	FlockForce = FVector::Zero();
}

void AHornetController::ToggleFlockState(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Cyan, FString::Printf(TEXT("Flock State Change Fired")));
	if (CurrentState == Soldier) 
	{
		CurrentState = Worker;
	}
	else if (CurrentState == Worker)
	{
		CurrentState = Soldier;
	}
}