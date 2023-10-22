#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ship.generated.h"

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

	UFUNCTION(BlueprintCallable)
	void SetControl(APlayerCharacter* Player);

	void SetUpInputs(UEnhancedInputComponent* EnhancedInputComponent, const UInputAction* MoveAction);
	void RemoveInputs(UEnhancedInputComponent* EnhancedInputComponent) const;

protected:

	virtual void BeginPlay() override;

private:

	void Move(const FInputActionValue& Value);

public:

	UPROPERTY(BlueprintReadWrite)
	TArray<AShipPiece*> Engines;

private:

	uint32 MoveActionHandle;

	UPROPERTY(Replicated)
	APlayerCharacter* ControllingPlayer = nullptr;

};
