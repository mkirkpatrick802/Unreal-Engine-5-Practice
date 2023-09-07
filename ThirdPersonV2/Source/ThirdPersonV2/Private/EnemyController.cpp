#include "EnemyController.h"

#include "BehaviorTree/BlackboardComponent.h"

void AEnemyController::InitController()
{
	if(!GetBlackBoard())
	{
		//UBlackboardComponent* BB = NewObject(this, TEXT("ThisIsMyTestFName"));
	}
}

UBlackboardComponent* AEnemyController::GetBlackBoard()
{
	return _blackboard;
}

void AEnemyController::SetBlackBoard(UBlackboardComponent* blackboard)
{
	_blackboard = blackboard;
}
