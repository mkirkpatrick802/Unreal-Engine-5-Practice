#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "StingerAnimInstance.generated.h"

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
	bool IsInAir;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool IsAccelerating;
};
