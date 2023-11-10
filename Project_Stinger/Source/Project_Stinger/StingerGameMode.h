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

private:

	Octree* HornetOctree;

};



