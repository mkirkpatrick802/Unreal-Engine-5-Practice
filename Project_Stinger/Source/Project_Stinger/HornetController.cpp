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
}

void AHornetController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateNeighbourhood();
	UpdateFlock();
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

	// TODO: Test This
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