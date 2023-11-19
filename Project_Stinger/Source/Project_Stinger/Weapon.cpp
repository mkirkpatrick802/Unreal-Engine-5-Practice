#include "Weapon.h"

#include "Projectile.h"
#include "StingerCharacter.h"
#include "Engine/SkeletalMeshSocket.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetupAttachment(RootComponent);
	SetRootComponent(WeaponMesh);

	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::Fire(const FVector& HitTarget)
{
	if(FireAnimation)
	{
		WeaponMesh->PlayAnimation(FireAnimation, false);
	}

	if (!HasAuthority()) return;

	APawn* InstigatorPawn = Cast<APawn>(GetOwner());
	const USkeletalMeshSocket* MuzzleFlashSocket = WeaponMesh->GetSocketByName(FName("Muzzle_Flash_Position"));
	if(MuzzleFlashSocket)
	{

		FTransform SocketTransform;
		FRotator TargetRotation;

		if(AStingerCharacter* Character = Cast<AStingerCharacter>(GetOwner()))
		{

			SocketTransform = MuzzleFlashSocket->GetSocketTransform(WeaponMesh);

			if(Character->IsAiming())
			{
				const FVector TargetDirection = HitTarget - SocketTransform.GetLocation();
				TargetRotation = TargetDirection.Rotation();
			}
			else
			{
				TargetRotation = SocketTransform.GetRotation().Rotator();
			}
		}

		if(ProjectileClass && InstigatorPawn)
		{
			UWorld* World = GetWorld();
			if(World)
			{
				FActorSpawnParameters SpawnParameters;
				SpawnParameters.Owner = GetOwner();
				SpawnParameters.Instigator = InstigatorPawn;

				World->SpawnActor<AProjectile>(ProjectileClass, SocketTransform.GetLocation(), TargetRotation, SpawnParameters);
			}
		}
	}
}