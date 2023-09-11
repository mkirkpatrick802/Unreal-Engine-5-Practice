#pragma once

#include "Math/Vector.h"
#include "Math/UnrealMathUtility.h"
#include "NavigationSystem.h"

//Last Header
#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

struct ForceConstants
{

public:
	const float _wanderingConstant = 1000;
	const float _separationConstant = 1000;
};

UCLASS()
class THIRDPERSONV2_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Enemy|Utility|")
		void InitController();

	UFUNCTION(BlueprintCallable, Category = "Enemy|Movement|")
		void AddForceDirection(FVector directionToBeAdded);

	UFUNCTION(BlueprintCallable, Category = "Enemy|Movement|")
		void Flocking(const TArray<AActor*>& neighbours);

	//Flocking Calculations
	void CalculateSeperationDirection(const TArray<AActor*>& neighbours);
	void CalculateCohesionDirection(const TArray<AActor*>& neighbours);
	void CalculateAlignmentDirection(const TArray<AActor*>& neighbours);

	void SetCurrentForceDirection(FVector dir) { _currentForceDirection = dir; }
	FVector GetCurrentForceDirection() const { return _currentForceDirection; }

private:

	//Constants
	const float _dampingConstant = .2;

	FVector _currentForceDirection;

};
