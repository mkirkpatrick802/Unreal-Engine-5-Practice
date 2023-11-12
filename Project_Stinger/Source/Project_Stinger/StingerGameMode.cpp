#include "StingerGameMode.h"

#include "EngineUtils.h"
#include "Hornet.h"
#include "Octree.h"
#include "UObject/ConstructorHelpers.h"

AStingerGameMode::AStingerGameMode()
{

	PrimaryActorTick.bCanEverTick = true;

	//Sets default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Project_Stinger/Blueprints/BP_StingerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	HornetOctree = Octree::Create(FVector(0, 0, 1000), 1000, 2);
}

void AStingerGameMode::BeginPlay()
{
	Super::BeginPlay();

	for (AHornet* Hornet : TActorRange<AHornet>(GetWorld()))
	{
		Hornet->SetTree(HornetOctree);
	}
}

void AStingerGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	HornetOctree->Clear();
	for (AHornet* Hornet : TActorRange<AHornet>(GetWorld()))
	{
		HornetOctree->Insert(Hornet);
	}
}