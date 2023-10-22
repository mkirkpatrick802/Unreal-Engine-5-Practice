#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class AShip;
class UInputAction;
class UInputMappingContext;

UCLASS()
class PROJECT_STEEL_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	APlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void ToggleShipControl(AShip* Ship);

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* DefaultContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* FlyAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* InteractAction;

private:

	void Rotate();
	FRotator RotateToMouse();

	UFUNCTION(Server, Unreliable)
	void ServerRotate(bool IsMoving, FRotator Rotator);

	void Move(const FInputActionValue& Value);
	void StopMoving(const FInputActionValue& Value);

	void StopFlying();
	void FlyingDelta(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable)
	void ServerSetFlying(bool Value, bool Timer = false);

	void LandingTimerBuffer(bool Value);

	UFUNCTION(Server, Reliable)
	void ServerLandingTimer(bool Value);

	void Interact(const FInputActionValue& Value);

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector MouseWorldLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector MouseWorldDirection;

private:

	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent;

	UPROPERTY(VisibleAnywhere, Category=Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Camera)
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	class USphereComponent* GroundCheck;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* OverHeadWidget;

	UPROPERTY(VisibleAnywhere, Category = Building)
	class UPlayerBuildSystem* PlayerBuildSystem;

	UPROPERTY(Replicated)
	bool IsCurrentlyMoving = false;

	UPROPERTY(Replicated)
	bool IsFlying = false;

	UPROPERTY(Replicated)
	AShip* ControllingShip = nullptr;
};
