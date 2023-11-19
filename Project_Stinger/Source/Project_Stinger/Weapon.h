#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class PROJECT_STINGER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	

	AWeapon();
	virtual void Tick(float DeltaTime) override;
	virtual void FireWeapon();
	virtual void SpawnProjectile(const FVector& HitTarget);

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	class UAnimationAsset* FireAnimation;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> ProjectileClass;

public:	

	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() { return WeaponMesh; }

};
