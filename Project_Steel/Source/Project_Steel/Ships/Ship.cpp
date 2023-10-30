#include "Ship.h"

#include "CockpitInterface.h"
#include "EngineInterface.h"
#include "EnhancedInputComponent.h"
#include "ShipPiece.h"
#include "ShipPieceInterface.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"
#include "Project_Steel/Player/PlayerCharacter.h"

#define ECC_BuildPreview ECC_GameTraceChannel1
#define ECC_ShipContainer ECC_GameTraceChannel5
#define ECC_ShipPiece ECC_GameTraceChannel3
#define ECC_BuildSocket ECC_GameTraceChannel2
#define ECC_Buildable ECC_GameTraceChannel4

AShip::AShip()
{
	PrimaryActorTick.bCanEverTick = true;

	//Networking
	bReplicates = true;
}

void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShip::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AShip, IsControlled);
}

void AShip::BeginPlay()
{
	Super::BeginPlay();
}

void AShip::SetUpInputs(UEnhancedInputComponent* EnhancedInputComponent, const UInputAction* MoveAction)
{
	IsControlled = true;
	MoveStartedActionHandle = EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShip::Move).GetHandle();
	MoveCompletedActionHandle = EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AShip::Move).GetHandle();
	MoveCanceledActionHandle = EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Canceled, this, &AShip::Move).GetHandle();
}

void AShip::RemoveInputs(UEnhancedInputComponent* EnhancedInputComponent)
{
	IsControlled = false;
	ActiveCockpit = nullptr;
	EnhancedInputComponent->RemoveBindingByHandle(MoveStartedActionHandle);
	EnhancedInputComponent->RemoveBindingByHandle(MoveCompletedActionHandle);
	EnhancedInputComponent->RemoveBindingByHandle(MoveCanceledActionHandle);
}

// TODO: Clean this Up 
void AShip::Move(const FInputActionValue& Value)
{
	const ICockpitInterface* CockpitInterface = Cast<ICockpitInterface>(ActiveCockpit);
	FVector CockpitForwardVector = CockpitInterface->Execute_GetLocalForward(ActiveCockpit);

	const FVector MoveVector = Value.Get<FVector>();

	if (MoveVector.Y == -1)
		CockpitForwardVector = CockpitForwardVector * -1;

	TArray<AShipPiece*> CorrectEngines;
	for (AShipPiece* Check : Engines)
	{
		const IEngineInterface* EngineInterface = Cast<IEngineInterface>(Check);
		EngineInterface->Execute_ToggleMaterial(Check, false);
		FVector PushVector = EngineInterface->Execute_GetPushVector(Check);

		if (MoveVector.Y != 0 && PushVector.Normalize() == CockpitForwardVector.Normalize())
		{
			CorrectEngines.AddUnique(Check);
		}
	}

	for (AShipPiece* CorrectEngine : CorrectEngines)
	{
		const IEngineInterface* EngineInterface = Cast<IEngineInterface>(CorrectEngine);
		EngineInterface->Execute_ToggleMaterial(CorrectEngine, true);

		FVector ForceDirection = EngineInterface->Execute_GetPushVector(CorrectEngine).GetSafeNormal2D();
		const float ForcePower = EngineInterface->Execute_GetForce(CorrectEngine);
		const FVector TotalForce = ForceDirection * ForcePower;

		//RootCollisionComponent->AddForce(TotalForce, NAME_None, false);
	}
}