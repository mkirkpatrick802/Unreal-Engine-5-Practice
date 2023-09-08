#include "EnemyController.h"

void AEnemyController::InitController()
{

}

void AEnemyController::AddForceDirection(FVector directionToBeAdded)
{
	_currentForceDirection += directionToBeAdded;
    _currentForceDirection = _currentForceDirection.GetSafeNormal();
}