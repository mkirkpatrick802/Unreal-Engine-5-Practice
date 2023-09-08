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
public:

	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Enemy|Utility|")
		void InitController();

	UFUNCTION(BlueprintCallable, Category = "Enemy|Movement|")
	void AddForceDirection(FVector directionToBeAdded);


	//void Move();
	FVector GetCurrentForceDirection() const { return _currentForceDirection; }

private:

	//Constants
	const float _dampingConstant = .2;
	const float _wanderingConstant = 1000;

	FVector _currentForceDirection;

};
