#include "CombatComponent.h"

#include "StingerCharacter.h"
#include "StingerPlayerController.h"
#include "Weapon.h"
#include "GameFramework/CharacterMovementComponent.h"
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

	FHitResult HitResult;
	TraceUnderCrosshairs(HitResult);
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

			// calculate crosshair spread
			// [0, 600] -> [0, 1]
			FVector2D WalkSpeedRange(0, Character->GetCharacterMovement()->MaxWalkSpeed);
			FVector2D VelocityMultiplierRange(0, 1);
			FVector Velocity = Character->GetVelocity();
			Velocity.Z = 0;

			CrosshairVelocityFactor = FMath::GetMappedRangeValueClamped(WalkSpeedRange, VelocityMultiplierRange, Velocity.Size());

			if(Character->GetCharacterMovement()->IsFalling())
			{
				CrosshairInAirFactor = FMath::FInterpTo(CrosshairInAirFactor, 2.25f, DeltaTime, 2.25f);
			}
			else
			{
				CrosshairInAirFactor = FMath::FInterpTo(CrosshairInAirFactor, 0.f, DeltaTime, 30.f);
			}

			Package.CrosshairSpread = CrosshairVelocityFactor + CrosshairInAirFactor;

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

		if(Character)
		{
			float DistanceToCharacter = (Character->GetActorLocation() - Start).Size();
			Start += CrosshairWorldDirection * (DistanceToCharacter + 100);
		}

		FVector End = Start + CrosshairWorldDirection * TRACE_LENGTH;

		GetWorld()->LineTraceSingleByChannel(TraceHitResult, Start, End, ECC_Visibility);

		if (TraceHitResult.ImpactPoint.IsZero())
		{
			TraceHitResult.ImpactPoint = End;
		}

		if(TraceHitResult.GetActor() && TraceHitResult.GetActor()->Implements<UInteractWithCrosshairsInterface>())
		{
			Package.CrosshairsColor = FLinearColor::Red;
		}
		else
		{
			Package.CrosshairsColor = FLinearColor::White;
		}
	}
}