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

	Hornets.Empty();

	for (AHornet* Hornet : TActorRange<AHornet>(GetWorld()))
	{
		Hornet->SetTree(HornetOctree);
		Hornets.AddUnique(Hornet);
	}

	HornetOctree->Clear();
	for (AHornet* Hornet : Hornets)
		HornetOctree->Insert(Hornet);

	HornetOctree->Resize();
	HornetOctree->DrawDebug(GetWorld());
}