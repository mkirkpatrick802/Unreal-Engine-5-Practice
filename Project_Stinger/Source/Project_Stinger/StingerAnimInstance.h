#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "StingerAnimInstance.generated.h"

enum class ETurningInPlace : uint8;
class AStingerCharacter;

UCLASS()
class PROJECT_STINGER_API UStingerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

protected:

	UPROPERTY(BlueprintReadOnly, Category= Character)
	AStingerCharacter* StingerCharacter;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float Speed;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float AO_Pitch;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool IsInAir;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool IsAccelerating;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool IsCrouched;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool IsAiming;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	class AWeapon* EquippedWeapon;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	FTransform LeftHandTransform;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	ETurningInPlace TurningInPlace;
};
