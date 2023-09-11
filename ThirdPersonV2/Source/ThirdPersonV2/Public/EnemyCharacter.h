#pragma once

#include "EnemyController.h"

//Last Header
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UENUM(BlueprintType)
enum EEnemyState
{
	Wander			UMETA(DisplayName = "Wandering"),
	Flocking		UMETA(DisplayName = "Flocking"),
};

UCLASS()
class THIRDPERSONV2_API AEnemyCharacter : public ACharacter
{
public:

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Enums|")
		TEnumAsByte <EEnemyState> EnemyState;

	// Sets default values for this character's properties
	AEnemyCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Move();

	bool IsCharacterLeavingNavmesh();
	void StartReturnCooldown();

	UFUNCTION(BlueprintCallable, Category = "Enemy|State|")
		void SetCurrentState(EEnemyState state) { currentState = state; }

protected:



private:

	EEnemyState currentState;
	bool _atBorder = false;
	AEnemyController* _controller;
};
