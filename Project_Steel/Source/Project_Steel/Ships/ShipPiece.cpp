#include "ShipPiece.h"

#include "Ship.h"
#include "Net/UnrealNetwork.h"


AShipPiece::AShipPiece() :
	Ship(nullptr)
{
	PrimaryActorTick.bCanEverTick = false;
}

void AShipPiece::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle DelayHandle;
	GetWorldTimerManager().SetTimer(DelayHandle, this, &AShipPiece::CreateNewShip, 0.01f, false);
}

void AShipPiece::CreateNewShip()
{
	if (!Ship)
	{
		ServerSpawnShipParent(GetTransform(), AShip::StaticClass());
	}
}

void AShipPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShipPiece::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AShipPiece, Ship);
}

void AShipPiece::ServerSpawnShipParent_Implementation(const FTransform SpawnTransform, UClass* ToSpawn)
{
	Ship = GetWorld()->SpawnActor<AShip>(ToSpawn, SpawnTransform);
	if (AttachToActor(Ship, FAttachmentTransformRules::KeepWorldTransform))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Green,
				FString::Printf(TEXT("Ship Made"))
			);
		}
	}
}
