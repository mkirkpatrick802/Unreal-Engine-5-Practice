#pragma once

#include "Math/Vector.h"
#include "Math/UnrealMathUtility.h"
#include "NavigationSystem.h"

//Last Header
#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

UENUM(BlueprintType)
enum EConstantTypes
{
	Wandering		UMETA(DisplayName = "Wandering"),
	Seperation		UMETA(DisplayName = "Seperation"),
	Cohesion		UMETA(DisplayName = "Cohesion"),
	Alignment		UMETA(DisplayName = "Alignment"),
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
		void Flocking(const TArray<AActor*>& c_neighbours, int c_length, const TArray<AActor*>& s_neighbours, int s_length);

	//Flocking Calculations
	void CalculateSeperationDirection(const TArray<AActor*>& neighbours, int length);
	void CalculateCohesionDirection(const TArray<AActor*>& neighbours, int length);
	void CalculateAlignmentDirection(const TArray<AActor*>& neighbours, int length);

	void SetCurrentForceDirection(FVector dir) { _currentForceDirection = dir; }
	FVector GetCurrentForceDirection() const { return _currentForceDirection; }

	UFUNCTION(BlueprintCallable, Category = "Enemy|Utility|")
		static void SetConstant(EConstantTypes type, float value);

	inline static float wanderingConstant = 0;
	inline static float separationConstant = 0;
	inline static float cohesionConstant = 0;
	inline static float alignmentConstant = 0;

	FVector separationDirection;
	FVector cohesionDirection;
	FVector alignmentDirection;

private:

	//Constants
	const float _dampingConstant = .2;


	FVector _currentForceDirection;
};
