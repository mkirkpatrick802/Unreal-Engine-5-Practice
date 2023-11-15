#pragma once

#include "CoreMinimal.h"
#include "Octree.h"
#include "GameFramework/GameModeBase.h"
#include "StingerGameMode.generated.h"

class AHornet;

UCLASS(minimalapi)
class AStingerGameMode : public AGameModeBase
{

	GENERATED_BODY()

public:

	AStingerGameMode();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:

	Octree* HornetOctree;

	UPROPERTY()
	TArray<AHornet*> Hornets;

	UPROPERTY(EditAnywhere)
	float OctreeStartingHalfWidth = 5000;
};