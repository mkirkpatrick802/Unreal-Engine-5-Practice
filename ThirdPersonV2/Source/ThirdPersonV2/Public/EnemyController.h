#pragma once

#include "EnemyCharacter.h"

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

UCLASS()
class THIRDPERSONV2_API AEnemyController : public AAIController
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Enemy|Utility|")
		void InitController();


	UBlackboardComponent* GetBlackBoard();
	void SetBlackBoard(UBlackboardComponent* blackboard);

private:

	UBlackboardComponent* _blackboard;

};
