#include "Ship.h"

#include "EnhancedInputComponent.h"
#include "Net/UnrealNetwork.h"
#include "Project_Steel/Player/PlayerCharacter.h"


AShip::AShip()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	Root->SetupAttachment(Root);
	SetRootComponent(Root);

	bReplicates = true;
}

void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShip::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AShip, ControllingPlayer);
}

void AShip::BeginPlay()
{
	Super::BeginPlay();
}

void AShip::SetControl(APlayerCharacter* Player)
{
	if (!Player) return;

	if (ControllingPlayer == Player)
	{
		ControllingPlayer->ToggleShipControl(this);
		ControllingPlayer = nullptr;
	}
	else if (!ControllingPlayer)
	{
		ControllingPlayer = Player;
		ControllingPlayer->ToggleShipControl(this);
	}
}

void AShip::SetUpInputs(UEnhancedInputComponent* EnhancedInputComponent, const UInputAction* MoveAction)
{
	MoveActionHandle = EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShip::Move).GetHandle();
}

void AShip::RemoveInputs(UEnhancedInputComponent* EnhancedInputComponent) const
{
	EnhancedInputComponent->RemoveBindingByHandle(MoveActionHandle);
}

void AShip::Move(const FInputActionValue& Value)
{

}