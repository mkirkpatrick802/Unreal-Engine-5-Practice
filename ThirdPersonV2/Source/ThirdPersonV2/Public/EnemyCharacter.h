#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UENUM(BlueprintType)
enum EEnemyState
{
	IdleWander		UMETA(DisplayName = "Wander"),
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

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

};
