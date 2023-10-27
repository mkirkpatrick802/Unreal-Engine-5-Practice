#include "Ship.h"

#include "CockpitInterface.h"
#include "EngineInterface.h"
#include "EnhancedInputComponent.h"
#include "ShipPiece.h"
#include "Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Project_Steel/Player/PlayerCharacter.h"

#define ECC_ShipContainer ECC_GameTraceChannel5
#define ECC_ShipPiece ECC_GameTraceChannel3

AShip::AShip()
{
	PrimaryActorTick.bCanEverTick = true;

	RootMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root Component"));
	RootMeshComponent->SetupAttachment(RootMeshComponent);
	RootMeshComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	RootMeshComponent->SetCollisionObjectType(ECC_ShipContainer);
	RootMeshComponent->SetCollisionResponseToChannel(ECC_ShipPiece, ECR_Ignore);
	RootMeshComponent->SetSimulatePhysics(true);

	SetRootComponent(RootMeshComponent);

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

void AShip::AddShipPiece(AShipPiece* ShipPiece, FTransform PieceTransform)
{
	//ShipPiece->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

	UPhysicsConstraintComponent* NewPhysicsConstraintComponent = NewObject<UPhysicsConstraintComponent>(this, FName("Physics Constraint"));
	NewPhysicsConstraintComponent->RegisterComponent();
	NewPhysicsConstraintComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	NewPhysicsConstraintComponent->ComponentName1.ComponentName = FName(GetRootComponent()->GetName());
	NewPhysicsConstraintComponent->ComponentName2.ComponentName = FName(ShipPiece->GetRootComponent()->GetName());

	NewPhysicsConstraintComponent->ConstraintActor1 = this;
	NewPhysicsConstraintComponent->ConstraintActor2 = ShipPiece;

	NewPhysicsConstraintComponent->SetLinearXLimit(LCM_Locked, 0);
	NewPhysicsConstraintComponent->SetLinearYLimit(LCM_Locked, 0);
	NewPhysicsConstraintComponent->SetLinearZLimit(LCM_Locked, 0);

	NewPhysicsConstraintComponent->ConstraintInstance.SetLinearXMotion(LCM_Locked);
	NewPhysicsConstraintComponent->ConstraintInstance.SetLinearYMotion(LCM_Locked);
	NewPhysicsConstraintComponent->ConstraintInstance.SetLinearZMotion(LCM_Locked);

	NewPhysicsConstraintComponent->ConstraintInstance.SetAngularSwing1Motion(ACM_Locked);
	NewPhysicsConstraintComponent->ConstraintInstance.SetAngularSwing2Motion(ACM_Locked);
	NewPhysicsConstraintComponent->ConstraintInstance.SetAngularTwistMotion(ACM_Locked);

	NewPhysicsConstraintComponent->ConstraintInstance.EnableParentDominates();
	PhysicsConstraintComponent = NewPhysicsConstraintComponent;


	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Green,
			FString::Printf(TEXT("%i"), NewPhysicsConstraintComponent->IsBroken())
		);
	}
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
		float ForcePower = EngineInterface->Execute_GetForce(CorrectEngine);

		RootMeshComponent->AddForce(ForceDirection * ForcePower, NAME_None, true);
	}
}