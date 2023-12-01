// Copyright Epic Games, Inc. All Rights Reserved.

#include "StingerCharacter.h"

#include "CombatComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Weapon.h"
#include "Net/UnrealNetwork.h"


//////////////////////////////////////////////////////////////////////////
// AProject_StingerCharacter

AStingerCharacter::AStingerCharacter()
{

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->SocketOffset.Z = 40;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	//Create a combat component
	Combat = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
	Combat->SetIsReplicated(true);
}

void AStingerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if(Combat)
	{
		Combat->Character = this;
	}
}

void AStingerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AStingerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AimOffset(DeltaSeconds);
	HideCameraIfCharacterClose();
}

void AStingerCharacter::HideCameraIfCharacterClose()
{
	if (!IsLocallyControlled()) return;
	if ((FollowCamera->GetComponentLocation() - GetActorLocation()).Size() < CameraThreshold)
	{
		GetMesh()->SetVisibility(false);
		if (Combat && Combat->CurrentWeapon && Combat->CurrentWeapon->GetWeaponMesh())
		{
			Combat->CurrentWeapon->GetWeaponMesh()->bOwnerNoSee = true;
		}
	}
	else
	{
		GetMesh()->SetVisibility(true);
		if (Combat && Combat->CurrentWeapon && Combat->CurrentWeapon->GetWeaponMesh())
		{
			Combat->CurrentWeapon->GetWeaponMesh()->bOwnerNoSee = false;
		}
	}
}

void AStingerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AStingerCharacter::SetWeapon(AWeapon* Weapon)
{
	EquipWeapon = Weapon;
	Combat->CurrentWeapon = Weapon;
}

AWeapon* AStingerCharacter::GetEquippedWeapon() const
{
	return EquipWeapon;
}

bool AStingerCharacter::IsAiming() const
{
	return (Combat && Combat->IsAiming);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AStingerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Canceled, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AStingerCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AStingerCharacter::Look);

		//Crouching
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AStingerCharacter::ToggleCrouch);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AStingerCharacter::ToggleCrouch);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Canceled, this, &AStingerCharacter::ToggleCrouch);

		//Aim
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &AStingerCharacter::ToggleAim);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &AStingerCharacter::ToggleAim);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Canceled, this, &AStingerCharacter::ToggleAim);

		//Fire
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &AStingerCharacter::ToggleFireWeapon);
	}
}

void AStingerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AStingerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AStingerCharacter::ToggleCrouch(const FInputActionValue& Value)
{
	if(bIsCrouched)
	{
		UnCrouch();
	}
	else
	{
		Crouch();
	}
}

void AStingerCharacter::ToggleAim(const FInputActionValue& Value)
{
	if (Combat)
	{
		Combat->ToggleAiming();

		bUseControllerRotationYaw = Combat->IsAiming;
		GetCharacterMovement()->bOrientRotationToMovement = !Combat->IsAiming;
		ServerUpdateControlRotation(Combat->IsAiming);

		CameraBoom->TargetArmLength = Combat->IsAiming ? FMath::Lerp(200, 500, 0.1f) : FMath::Lerp(500, 200, 0.1f);
		CameraBoom->SocketOffset.Y = Combat->IsAiming ? FMath::Lerp(75, 80, 0.1f) : FMath::Lerp(80, 75, 0.1f);
		CameraBoom->SocketOffset.Z = Combat->IsAiming ? FMath::Lerp(75, 80, 0.1f) : FMath::Lerp(80, 75, 0.1f);
	}
}


void AStingerCharacter::ServerUpdateControlRotation_Implementation(bool SetControlRotationYaw)
{
	bUseControllerRotationYaw = SetControlRotationYaw;
}

void AStingerCharacter::AimOffset(float DeltaTime)
{
	if(!IsAiming())
	{
		AO_Pitch = 0;
		AO_Yaw = 0;
		return;
	}

	AO_Pitch = GetBaseAimRotation().Pitch;
	if(AO_Pitch > 90.f && !IsLocallyControlled())
	{
		// Map pitch from [270, 360) to [-90, 0)
		const FVector2D InRange(270.f, 360.f);
		const FVector2D OutRange(-90.f, 0.f);
		AO_Pitch = FMath::GetMappedRangeValueClamped(InRange, OutRange, AO_Pitch);
	}
}

void AStingerCharacter::ToggleFireWeapon()
{

	if(Combat)
		Combat->Fire();
}

void AStingerCharacter::Hit()
{
	IBulletHitInterface::Hit();


}

void AStingerCharacter::PlayFireMontage()
{
	if(Combat)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if(AnimInstance && FireWeaponMontage)
		{
			AnimInstance->Montage_Play(FireWeaponMontage);
		}
	}
}
