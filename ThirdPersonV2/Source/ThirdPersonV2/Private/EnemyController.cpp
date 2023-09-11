#include "EnemyController.h"

void AEnemyController::InitController()
{

}

void AEnemyController::AddForceDirection(FVector directionToBeAdded)
{
	_currentForceDirection += directionToBeAdded;
    _currentForceDirection = _currentForceDirection.GetSafeNormal();
}

void AEnemyController::Flocking(const TArray<AActor*>& neighbours)
{

}

void AEnemyController::CalculateSeperationDirection(const TArray<AActor*>& neighbours)
{

}

void AEnemyController::CalculateCohesionDirection(const TArray<AActor*>& neighbours)
{

}

void AEnemyController::CalculateAlignmentDirection(const TArray<AActor*>& neighbours)
{

}
