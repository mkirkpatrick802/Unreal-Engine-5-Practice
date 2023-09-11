#pragma once

#include "Math/Vector.h"
#include "Math/UnrealMathUtility.h"
#include "NavigationSystem.h"

//Last Header
#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

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
		void Flocking(const TArray<AActor*>& neighbours, int length);

	//Flocking Calculations
	void CalculateSeperationDirection(const TArray<AActor*>& neighbours, int length);
	void CalculateCohesionDirection(const TArray<AActor*>& neighbours, int length);
	void CalculateAlignmentDirection(const TArray<AActor*>& neighbours, int length);

	void SetCurrentForceDirection(FVector dir) { _currentForceDirection = dir; }
	FVector GetCurrentForceDirection() const { return _currentForceDirection; }

	const float separationConstant = 1000;
	const float wanderingConstant = 1000;
	const float cohesionConstant = 1000;
	const float alignmentConstant = 1000;

	FVector separationDirection;
	FVector cohesionDirection;
	FVector alignmentDirection;

private:

	//Constants
	const float _dampingConstant = .2;


	FVector _currentForceDirection;
};
