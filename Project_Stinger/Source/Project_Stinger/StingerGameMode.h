#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StingerGameMode.generated.h"

class Octree;

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

	UPROPERTY(EditAnywhere)
	float OctreeHalfWidth = 10000;

	UPROPERTY(EditAnywhere)
	float OctreeDepth = 3;

};