// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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

	CharacterMovement = GetCharacterMovement();
	CharacterMovement->bOrientRotationToMovement = false;

	OverHeadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidget"));
	OverHeadWidget->SetupAttachment(RootComponent);
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

void APlayerCharacter::ServerRPCRotate_Implementation()
{

	if(CharacterMovement)
	{
		CharacterMovement->bOrientRotationToMovement = false;
	}

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
		}
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	IsMoving = true;

	if (CharacterMovement)
	{
		CharacterMovement->bOrientRotationToMovement = true;
	}

	const FVector2D MovementVector = Value.Get<FVector2D>();

	AddMovementInput(FVector(0.f, 1.f, 0.f), MovementVector.Y);

	const FVector Right = GetActorRightVector();
	AddMovementInput(FVector(1.f, 0.f, 0.f), MovementVector.X);
}

void APlayerCharacter::StopMoving(const FInputActionValue& Value)
{
	IsMoving = false;
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsMoving) ServerRPCRotate();
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopMoving);
	}
}

