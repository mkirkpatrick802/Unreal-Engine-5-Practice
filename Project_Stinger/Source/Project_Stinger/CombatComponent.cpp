#include "CombatComponent.h"

#include "StingerCharacter.h"
#include "StingerHUD.h"
#include "StingerPlayerController.h"
#include "Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCombatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCombatComponent, IsAiming);
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SetHUDCrosshairs(DeltaTime);
}


void UCombatComponent::SetHUDCrosshairs(float DeltaTime)
{
	if(Character == nullptr || Character->Controller == nullptr) return;

	Controller = Controller == nullptr ? Cast<AStingerPlayerController>(Character->Controller) : Controller;
	if (Controller)
	{
		HUD = HUD == nullptr ? Cast<AStingerHUD>(Controller->GetHUD()) : HUD;
		if (HUD && CurrentWeapon)
		{
			FHUDPackage Package;
			if(IsAiming)
			{
				Package.CrosshairsCenter = CurrentWeapon->CrosshairsCenter;
				Package.CrosshairsLeft = CurrentWeapon->CrosshairsLeft;
				Package.CrosshairsRight = CurrentWeapon->CrosshairsRight;
				Package.CrosshairsBottom = CurrentWeapon->CrosshairsBottom;
				Package.CrosshairsTop = CurrentWeapon->CrosshairsTop;
			}
			else
			{
				Package.CrosshairsCenter = nullptr;
				Package.CrosshairsLeft = nullptr;
				Package.CrosshairsRight = nullptr;
				Package.CrosshairsBottom = nullptr;
				Package.CrosshairsTop = nullptr;
			}
			HUD->SetHUDPackage(Package);
		}
	}
}

void UCombatComponent::ToggleAiming()
{
	IsAiming = !IsAiming;
	ServerSetAiming(IsAiming);
}

void UCombatComponent::ServerSetAiming_Implementation(bool Aiming)
{
	IsAiming = Aiming;
}

void UCombatComponent::Fire()
{
	FHitResult HitResult;
	TraceUnderCrosshairs(HitResult);
	ServerFire(HitResult.ImpactPoint);
}

void UCombatComponent::ServerFire_Implementation(const FVector_NetQuantize& TraceHitTarget)
{
	// Only spawn the projectile on the Server
	if (CurrentWeapon == nullptr) return;
	CurrentWeapon->SpawnProjectile(TraceHitTarget);
	MulticastFire(TraceHitTarget);
}

void UCombatComponent::MulticastFire_Implementation(const FVector_NetQuantize& TraceHitTarget)
{
	// Play The Weapon Animations on all clients
	if (Character)
	{
		Character->PlayFireMontage();
		CurrentWeapon->FireWeapon();
	}
}

void UCombatComponent::TraceUnderCrosshairs(FHitResult& TraceHitResult)
{
	FVector2D ViewportSize;
	if(GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
	}

	const FVector2D CrosshairLocation(ViewportSize.X / 2.f, ViewportSize.Y / 2.f);
	FVector CrosshairWorldPosition;
	FVector CrosshairWorldDirection;
	bool ScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(
		UGameplayStatics::GetPlayerController(this, 0),
		CrosshairLocation,
		CrosshairWorldPosition,
		CrosshairWorldDirection
	);

	if(ScreenToWorld)
	{
		FVector Start = CrosshairWorldPosition;
		FVector End = Start + CrosshairWorldDirection * TRACE_LENGTH;

		GetWorld()->LineTraceSingleByChannel(TraceHitResult, Start, End, ECC_Visibility);

	}
}