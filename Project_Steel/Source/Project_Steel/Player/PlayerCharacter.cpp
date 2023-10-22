#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerBuildSystem.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "Project_Steel/Ships/Ship.h"
#include "Project_Steel/Ships/ShipPiece.h"

#define ECC_ShipPiece ECC_GameTraceChannel3

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

	GroundCheck = CreateDefaultSubobject<USphereComponent>(TEXT("Ground Check"));
	GroundCheck->SetupAttachment(GetMesh());
	GroundCheck->InitSphereRadius(10);

	PlayerBuildSystem = CreateDefaultSubobject<UPlayerBuildSystem>(TEXT("Player Build System"));
}

void APlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerCharacter, IsCurrentlyMoving);
	DOREPLIFETIME(APlayerCharacter, IsFlying);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopMoving);

		//Flying
		EnhancedInputComponent->BindAction(FlyAction, ETriggerEvent::Started, this, &APlayerCharacter::FlyingDelta);
		EnhancedInputComponent->BindAction(FlyAction, ETriggerEvent::Canceled, this, &APlayerCharacter::FlyingDelta);
		EnhancedInputComponent->BindAction(FlyAction, ETriggerEvent::Completed, this, &APlayerCharacter::FlyingDelta);

		//Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APlayerCharacter::Interact);

		if(PlayerBuildSystem)
		{
			PlayerBuildSystem->SetUpInputs(EnhancedInputComponent);
		}
	}
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Map Inputs
	if(APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultContext, 0);
		}

		PlayerController->SetShowMouseCursor(true);
	}

	//Start Ground Check Timer
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &APlayerCharacter::StopFlying);
	float GroundCheckTimeInterval = .25f;
	GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, GroundCheckTimeInterval, true);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!ControllingShip)
		Rotate();
}

/*
 *
 *	Player Rotations
 *
 */

void APlayerCharacter::Rotate()
{
	if (HasAuthority())
	{
		RotateToMouse();
	}
	else
	{
		ServerRotate(false, RotateToMouse());
	}
}

FRotator APlayerCharacter::RotateToMouse()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (PlayerController->DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection))
		{
			if (!IsCurrentlyMoving)
			{
				FRotator Rotator = MouseWorldDirection.Rotation();
				Rotator = FMath::Lerp(GetActorRotation(), Rotator, .05f);
				Rotator.Pitch = 0;
				Rotator.Roll = 0;
				SetActorRotation(Rotator);

				return Rotator;
			}
		}
	}

	return FRotator(0, 0, 0);
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

/*
 *
 *	Player Movement
 *
 */

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	if(ControllingShip) return;

	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		MovementComponent->bOrientRotationToMovement = true;
	}

	ServerRotate(true, GetActorRotation());

	const FVector2D MovementVector = Value.Get<FVector2D>();
	AddMovementInput(FVector(0.f, 1.f, 0.f), MovementVector.Y);
	AddMovementInput(FVector(1.f, 0.f, 0.f), MovementVector.X);
}

void APlayerCharacter::StopMoving(const FInputActionValue& Value)
{
	ServerRotate(false, GetActorRotation());
}

/*
 *
 *	Player Flying
 *
 */

void APlayerCharacter::StopFlying()
{

	if(UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		if(MovementComponent->MovementMode == MOVE_Walking) return;
		if(GroundCheck)
		{

			//Create Query Object to pass into collision function
			FCollisionQueryParams TraceParams(FName(TEXT("GroundCheck")), true, this);

			//Peform a sphere sweep
			TArray<FHitResult> HitResults;
			FVector SphereCenter = GroundCheck->GetComponentLocation();
			float SphereRadius = GroundCheck->GetScaledSphereRadius();

			FCollisionObjectQueryParams ObjectParams;
			ObjectParams.AddObjectTypesToQuery(ECC_ShipPiece);

			if(GetWorld()->SweepMultiByObjectType(HitResults, SphereCenter, SphereCenter, FQuat::Identity, ObjectParams, FCollisionShape::MakeSphere(SphereRadius), TraceParams))
			{
				for (const FHitResult& Hit : HitResults)
				{
					AActor* HitActor = Hit.GetActor();
					if (HitActor->IsA(AShipPiece::StaticClass()))
					{
						switch (MovementComponent->MovementMode)
						{
						case MOVE_Falling:
						case MOVE_Flying:
							MovementComponent->SetMovementMode(MOVE_Walking);
							ServerSetFlying(false, true);
							break;
						}
					}
				}
			}
		}
	}
}

void APlayerCharacter::FlyingDelta(const FInputActionValue& Value)
{
	if (ControllingShip) return;

	ServerSetFlying(Value.Get<bool>());
}

void APlayerCharacter::ServerSetFlying_Implementation(bool Value, bool Timer)
{
	IsFlying = Value;

	if(!Timer)
	{
		if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
		{
			MovementComponent->bCanWalkOffLedges = Value;
		}
	}
	else
	{
		if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
		{
			MovementComponent->bCanWalkOffLedges = !Value;
		}

		FTimerHandle TimerHandle;
		FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &APlayerCharacter::LandingTimerBuffer, Value);
		GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, .1f, false);
	}
}

void APlayerCharacter::LandingTimerBuffer(bool Value)
{
	ServerLandingTimer(Value);
}

void APlayerCharacter::ServerLandingTimer_Implementation(bool Value)
{
	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		MovementComponent->bCanWalkOffLedges = Value;
	}
}

/*
 *
 *	Player Interactions
 *
 */

void APlayerCharacter::Interact(const FInputActionValue& Value)
{
	AActor* Interactable = nullptr;
	TArray<UPrimitiveComponent*> OverlappingComponents;
	Cast<UCapsuleComponent>(GetRootComponent())->GetOverlappingComponents(OverlappingComponents);
	for (auto i : OverlappingComponents)
	{
		if (!i->ComponentHasTag(FName("Interactable"))) continue;
		Interactable = i->GetOwner();
		break;
	}

	if (!Interactable) return;

	static_cast<AShipPiece*>(Interactable)->Interact(this);
}

void APlayerCharacter::ToggleShipControl(AShip* Ship)
{

	if(ControllingShip == Ship)
	{
		ControllingShip->RemoveInputs(EnhancedInputComponent);
		ControllingShip = nullptr;
		return;
	}

	if(Ship->GetIsControlled()) return;

	ControllingShip = Ship;

	if(PlayerBuildSystem)
		PlayerBuildSystem->SetBuildMode(false);

	ControllingShip->SetUpInputs(EnhancedInputComponent, MoveAction);
}