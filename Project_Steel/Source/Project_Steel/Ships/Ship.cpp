#include "Ship.h"


AShip::AShip()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	Root->SetupAttachment(Root);
	SetRootComponent(Root);
}

void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShip::BeginPlay()
{
	Super::BeginPlay();
}