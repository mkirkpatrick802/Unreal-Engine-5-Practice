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

	HornetOctree = Octree::Create(FVector(0, 0, OctreeStartingHalfWidth), OctreeStartingHalfWidth);
}

void AStingerGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AStingerGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	HornetOctree->Clear();
	for (AHornet* Hornet : Hornets)
		HornetOctree->Insert(Hornet);

	HornetOctree->Resize();

	if(DisplayOctree)
		HornetOctree->DrawDebug(GetWorld());
}

void AStingerGameMode::HornetSpawned(AHornet* Hornet)
{
	if(Hornet)
	{
		Hornet->SetTree(HornetOctree);
		Hornets.AddUnique(Hornet);
	}
}

void AStingerGameMode::HornetDestroyed(AHornet* Hornet)
{
	Hornets.Remove(Hornet);
}