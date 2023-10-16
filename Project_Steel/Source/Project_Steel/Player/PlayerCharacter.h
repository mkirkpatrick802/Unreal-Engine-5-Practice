#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class PROJECT_STEEL_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	APlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputMappingContext* DefaultContext;

	//Movement Inputs
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* FlyAction;

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


private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector MouseWorldLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector MouseWorldDirection;

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
};
