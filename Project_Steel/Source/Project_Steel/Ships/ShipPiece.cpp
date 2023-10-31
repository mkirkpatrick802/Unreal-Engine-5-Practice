#include "ShipPiece.h"

#include "Ship.h"
#include "Net/UnrealNetwork.h"
#include "Project_Steel/Player/PlayerCharacter.h"

#define ECC_ShipPiece ECC_GameTraceChannel3
#define ECC_ShipContainer ECC_GameTraceChannel5

AShipPiece::AShipPiece() :
	CurrentShip(nullptr)
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship Piece"));
	MeshComponent->SetupAttachment(GetRootComponent());
	SetRootComponent(MeshComponent);

	MeshComponent->SetCollisionObjectType(ECC_ShipPiece);
	MeshComponent->SetSimulatePhysics(false);
}

void AShipPiece::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle DelayHandle;
	GetWorldTimerManager().SetTimer(DelayHandle, this, &AShipPiece::CreateNewShip, 0.01f, false);
}

void AShipPiece::Interact_Implementation(APlayerCharacter* Player)
{

}

void AShipPiece::Placed_Implementation()
{

}

void AShipPiece::CreateNewShip()
{
	if (!CurrentShip)
	{
		FTransform SpawnTransform = GetTransform();
		SpawnTransform.SetLocation(FVector(SpawnTransform.GetLocation().X, SpawnTransform.GetLocation().Y, 200));
		ServerSpawnShipParent(GetTransform());
	}
}

void AShipPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShipPiece::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AShipPiece, CurrentShip);
}

void AShipPiece::ServerSpawnShipParent_Implementation(const FTransform SpawnTransform)
{
	CurrentShip = GetWorld()->SpawnActor<AShip>(AShip::StaticClass(), SpawnTransform);
	CurrentShip->AddShipPiece(this, GetTransform());
	Placed();
}
