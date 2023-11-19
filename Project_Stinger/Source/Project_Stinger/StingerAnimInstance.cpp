#include "StingerAnimInstance.h"

#include "StingerCharacter.h"
#include "Weapon.h"
#include "GameFramework/CharacterMovementComponent.h"

void UStingerAnimInstance::NativeInitializeAnimation()
{
	UAnimInstance::NativeInitializeAnimation();

	StingerCharacter = Cast<AStingerCharacter>(TryGetPawnOwner());
}

void UStingerAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	UAnimInstance::NativeUpdateAnimation(DeltaTime);

	if (!StingerCharacter) StingerCharacter = Cast<AStingerCharacter>(TryGetPawnOwner());
	if (!StingerCharacter) return;

	FVector Velocity = StingerCharacter->GetVelocity();
	Velocity.Z = 0;
	Speed = Velocity.Size();

	IsInAir = StingerCharacter->GetCharacterMovement()->IsFalling();
	IsAccelerating = StingerCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0 ? true : false;
	IsCrouched = StingerCharacter->bIsCrouched;
	IsAiming = StingerCharacter->IsAiming();
	AO_Pitch = StingerCharacter->GetAO_Pitch();
	TurningInPlace = StingerCharacter->GetTurningInPlace();

	EquippedWeapon = StingerCharacter->GetEquippedWeapon();
	if(EquippedWeapon && EquippedWeapon->GetWeaponMesh() && StingerCharacter->GetMesh())
	{
		USkeletalMeshComponent* WeaponMesh = EquippedWeapon->GetWeaponMesh();
		LeftHandTransform = WeaponMesh->GetSocketTransform(FName("LeftHandSocket"), RTS_World);

		FVector OutPosition;
		FRotator OutRotation;
		StingerCharacter->GetMesh()->TransformToBoneSpace(FName("Hand_R"), LeftHandTransform.GetLocation(), LeftHandTransform.Rotator(), OutPosition, OutRotation);
		LeftHandTransform.SetLocation(OutPosition);
		LeftHandTransform.SetRotation(FQuat(OutRotation));
	}
}
