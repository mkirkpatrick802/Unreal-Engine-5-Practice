#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ship.generated.h"

class UBoxComponent;
class UInputAction;
struct FInputActionValue;
class APlayerCharacter;
class AShipPiece;

UCLASS()
class PROJECT_STEEL_API AShip : public AActor
{
	GENERATED_BODY()
	
public:

	AShip();
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void SetUpInputs(UEnhancedInputComponent* EnhancedInputComponent, const UInputAction* MoveAction);
	void RemoveInputs(UEnhancedInputComponent* EnhancedInputComponent);

	UFUNCTION(BlueprintCallable)
	void SetActiveCockpit(AShipPiece* Cockpit) { ActiveCockpit = Cockpit; }

	bool GetIsControlled() const { return IsControlled; }

protected:

	virtual void BeginPlay() override;

private:

	void Move(const FInputActionValue& Value);

public:

	UPROPERTY(BlueprintReadWrite)
	TArray<AShipPiece*> Engines;

private:

	UPROPERTY()
	AShipPiece* ActiveCockpit;

	UPROPERTY()
	UBoxComponent* RootBoxComponent;

	uint32 MoveStartedActionHandle;
	uint32 MoveCompletedActionHandle;
	uint32 MoveCanceledActionHandle;

	UPROPERTY(Replicated)
	bool IsControlled = false;

};
