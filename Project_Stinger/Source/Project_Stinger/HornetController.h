#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "HornetController.generated.h"

class AHornet;
class Octree;
class UAISenseConfig_Sight;

UENUM(BlueprintType)
enum HornetStates
{
	Worker,
	Soldier,
};

UENUM(BlueprintType)
enum HornetActions
{
	Wandering,	// Both
	Swarming,	// Both
	Chase,		// Worker
	Charge,		// Soldier
	Fleeing,	// Worker
};

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


	// Setters
	FORCEINLINE void SetTree(Octree* Tree) { HornetOctree = Tree; }

private:

	void ChangeAction(HornetActions NewAction);

	UFUNCTION()
	void OnPawnDetected(AActor* Actor, FAIStimulus Stimulus);

	void UpdateNeighbourhood();

private:

	UPROPERTY()
	AHornet* Hornet;

	Octree* HornetOctree;
	TArray<AHornet*> Neighborhood;

	TEnumAsByte<HornetStates> CurrentState;
	TEnumAsByte<HornetActions> CurrentAction;
};
