#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "HornetController.generated.h"

class UAISenseConfig_Sight;

UENUM(BlueprintType)
enum HornetState
{
	Wandering = 0,
	Flocking,	// In this state the hornet will be preforming standard flocking behavior w/ Separation, Alignment, Cohesion
	Chase,			// In this state the hornet will be chasing a target while maintaining its formation w/ Separation, Cohesion
	Fleeing,		// In this state the hornet will be moving away from players and trying to regroup with it others
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

private:

	UFUNCTION()
	void OnPawnDetected(AActor* Actor, FAIStimulus Stimulus);

public:

	TEnumAsByte<HornetState> CurrentState;
};
