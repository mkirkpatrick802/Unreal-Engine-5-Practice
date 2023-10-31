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

	for (auto Element : GetComponents())
	{
		if(auto Box = Cast<UBoxComponent>(Element))
		{
			DrawDebugBox(GetWorld(), Box->GetComponentLocation(), Box->GetUnscaledBoxExtent(), Box->GetComponentRotation().Quaternion(), FColor::Red, false, .1, 0, 5.0f);
		}
	}

}

void AShip::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AShip, IsControlled);
}

void AShip::AddShipPiece(AShipPiece* ShipPiece, FTransform PieceTransform)
{

	const IShipPieceInterface* Interface = Cast<IShipPieceInterface>(ShipPiece);
	TArray<UBoxComponent*> Colliders = Interface->Execute_GetColliders(ShipPiece);

	UBoxComponent* NewBoxComponent = Cast<UBoxComponent>(AddComponentByClass(UBoxComponent::StaticClass(), false, FTransform(), false));
	NewBoxComponent->SetWorldTransform(PieceTransform);
	NewBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	NewBoxComponent->SetCollisionObjectType(ECC_ShipContainer);
	NewBoxComponent->SetCollisionResponseToChannel(ECC_ShipContainer, ECR_Block);
	NewBoxComponent->SetSimulatePhysics(true);

	NewBoxComponent->InitBoxExtent(Colliders[0]->GetUnscaledBoxExtent());

	ShipPiece->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
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

		Cast<UBoxComponent>(RootComponent)->AddForce(TotalForce, NAME_None, false);
	}
}