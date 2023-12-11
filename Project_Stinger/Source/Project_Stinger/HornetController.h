#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "HornetController.generated.h"

class AQueen;
class AHornet;
class Octree;
class UAISenseConfig_Sight;

UENUM(BlueprintType)
enum HornetStates
{
	NULLState = 0,
	Worker,
	Soldier,
};

UENUM(BlueprintType)
enum HornetActions
{
	NULLAction = 0,
	Wandering,		// Both
	Swarming,		// Worker
	Flocking,		// Soldier
	Chasing,		// Worker
	Charging,		// Soldier
	Fleeing,		// Worker
	Retreating,		// Soldier
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHornetActionDelegate, HornetActions, NewAction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHornetStateDelegate, HornetStates, NewState);

UCLASS()
class PROJECT_STINGER_API AHornetController : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere)
	UAISenseConfig_Sight* SightConfig;

public:

	AHornetController();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	FVector CalculateAvoidanceDirection();

	// Setters
	FORCEINLINE void SetTree(Octree* Tree) { HornetOctree = Tree; }

private:

	void ChangeAction(HornetActions NewAction);

	UFUNCTION()
	void OnPawnDetected(AActor* Actor, FAIStimulus Stimulus);

	void UpdateNeighbourhood();
	void UpdateFlock();
	void CalculateFlockForce();

public:

	FHornetActionDelegate ActionChangedEvent;
	FHornetStateDelegate StateChangedEvent;

private:

	UPROPERTY()
	AHornet* Hornet;

	UPROPERTY()
	AQueen* Queen;

	Octree* HornetOctree;
	TArray<AHornet*> Neighborhood;

	TEnumAsByte<HornetStates> CurrentState;
	TEnumAsByte<HornetActions> CurrentAction;

	TArray<AHornet*> Flock;

	FVector FlockForce;

	FVector OctreeBoundsMin;
	FVector OctreeBoundsMax;
};
