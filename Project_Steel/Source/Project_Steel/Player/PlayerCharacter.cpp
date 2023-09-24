// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 1000.f;
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bInheritYaw = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;

	OverHeadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidget"));
	OverHeadWidget->SetupAttachment(RootComponent);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsCurrentlyMoving) Rotate();
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopMoving);
	}
}

void APlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerCharacter, IsCurrentlyMoving);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultContext, 0);
		}

		PlayerController->SetShowMouseCursor(true);
	}
}

FRotator APlayerCharacter::RotateToMouse()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		FVector MouseWorldLocation;
		FVector MouseWorldDirection;
		if (PlayerController->DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection))
		{
			FRotator Rotator = MouseWorldDirection.Rotation();
			Rotator = FMath::Lerp(PlayerController->GetPawn()->GetActorRotation(), Rotator, .1f);
			Rotator.Pitch = 0;
			Rotator.Roll = 0;
			SetActorRotation(Rotator);

			return Rotator;
		}
	}

	return FRotator(0, 0, 0);
}

void APlayerCharacter::Rotate()
{
	if(HasAuthority())
	{
		RotateToMouse();
	}
	else
	{
		ServerRotate(false, RotateToMouse());
	}
}

void APlayerCharacter::ServerRotate_Implementation(bool IsMoving, FRotator Rotator)
{
	IsCurrentlyMoving = IsMoving;

	if(IsCurrentlyMoving)
	{
		if(UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
		{
			MovementComponent->bOrientRotationToMovement = true;
		}
	}
	else
	{
		if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
		{
			MovementComponent->bOrientRotationToMovement = false;
		}

		SetActorRotation(Rotator);
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		MovementComponent->bOrientRotationToMovement = true;
	}

	ServerRotate(true);

	const FVector2D MovementVector = Value.Get<FVector2D>();
	AddMovementInput(FVector(0.f, 1.f, 0.f), MovementVector.Y);
	AddMovementInput(FVector(1.f, 0.f, 0.f), MovementVector.X);
}

void APlayerCharacter::StopMoving(const FInputActionValue& Value)
{
	ServerRotate(false);
}
