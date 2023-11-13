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

	for (AHornet* Hornet : TActorRange<AHornet>(GetWorld()))
	{
		Hornet->SetTree(HornetOctree);
	}

	for (AHornet* Hornet : TActorRange<AHornet>(GetWorld()))
	{
		Hornets.AddUnique(Hornet);
	}

}

void AStingerGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	HornetOctree->Clear();
	for (AHornet* Hornet : Hornets)
	{
		HornetOctree->Insert(Hornet);
	}

	HornetOctree->DrawDebug(GetWorld());

}