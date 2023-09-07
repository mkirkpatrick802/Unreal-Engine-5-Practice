#pragma once

#include "EnemyCharacter.h"
#include "Math/Vector.h"

//Last Header
#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

UCLASS()
class THIRDPERSONV2_API AEnemyController : public AAIController
{
public:

	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Enemy|Utility|")
		void InitController();

private:

};
