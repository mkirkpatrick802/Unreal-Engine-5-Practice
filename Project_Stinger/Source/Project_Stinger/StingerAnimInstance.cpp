#include "StingerAnimInstance.h"

#include "StingerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UStingerAnimInstance::NativeInitializeAnimation()
{
	UAnimInstance::NativeInitializeAnimation();

	StingerCharacter = Cast<AStingerCharacter>(TryGetPawnOwner());
}

void UStingerAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	UAnimInstance::NativeUpdateAnimation(DeltaTime);

	if(!StingerCharacter) StingerCharacter = Cast<AStingerCharacter>(TryGetPawnOwner());
	if(!StingerCharacter) return;

	FVector Velocity = StingerCharacter->GetVelocity();
	Velocity.Z = 0;
	Speed = Velocity.Size();

	IsInAir = StingerCharacter->GetCharacterMovement()->IsFalling();
	IsAccelerating = StingerCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0 ? true : false;
}
