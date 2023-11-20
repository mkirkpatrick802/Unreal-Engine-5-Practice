#pragma once

#include "CoreMinimal.h"
#include "StingerHUD.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

#define TRACE_LENGTH 80000

class AStingerHUD;
class AStingerPlayerController;
class AWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_STINGER_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()
	friend class AStingerCharacter;

public:	

	UCombatComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:

	virtual void BeginPlay() override;

	void ToggleAiming();

	UFUNCTION(Server, Reliable)
	void ServerSetAiming(bool Aiming);

	void Fire();

	UFUNCTION(Server, Reliable)
	void ServerFire(const FVector_NetQuantize& TraceHitTarget);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastFire(const FVector_NetQuantize& TraceHitTarget);

	void TraceUnderCrosshairs(FHitResult& TraceHitResult);

	void SetHUDCrosshairs(float DeltaTime);

private:

	UPROPERTY()
	AStingerCharacter* Character;

	UPROPERTY()
	AStingerPlayerController* Controller;

	UPROPERTY()
	AStingerHUD* HUD;

	UPROPERTY(Replicated)
	bool IsAiming;

	UPROPERTY()
	AWeapon* CurrentWeapon;

	//HUD & Crosshairs

	FHUDPackage Package;

	float CrosshairVelocityFactor;
	float CrosshairInAirFactor;
};