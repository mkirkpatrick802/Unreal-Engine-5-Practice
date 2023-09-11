#include "EnemyController.h"

#include "GameFramework/Character.h"

void AEnemyController::InitController()
{

}

void AEnemyController::AddForceDirection(FVector directionToBeAdded)
{
	_currentForceDirection += directionToBeAdded;
    _currentForceDirection = _currentForceDirection.GetSafeNormal();
}

void AEnemyController::Flocking(const TArray<AActor*>& neighbours, int length)
{
	CalculateSeperationDirection(neighbours, length);
    CalculateCohesionDirection(neighbours, length);
}

void AEnemyController::CalculateSeperationDirection(const TArray<AActor*>& neighbours, int length)
{
    FVector force;
    for (auto i = 0; i < length; ++i)
    {
        force += this->GetPawn()->GetActorLocation() - neighbours[i]->GetActorLocation();
    }

    separationDirection = force.GetSafeNormal();
}

void AEnemyController::CalculateCohesionDirection(const TArray<AActor*>& neighbours, int length)
{
    FVector center;
    for (auto i = 0; i < length; ++i)
    {
        center += neighbours[i]->GetActorLocation();
    }

    FVector force;
    force = center - GetPawn()->GetActorLocation();
    cohesionDirection = force.GetSafeNormal();
}

void AEnemyController::CalculateAlignmentDirection(const TArray<AActor*>& neighbours, int length)
{
    FVector averageVelocity;
    for (auto i = 0; i < length; ++i)
    {
        //averageVelocity += i->getVel();
    }

    averageVelocity = averageVelocity / length + 1;
    alignmentDirection = averageVelocity;
}
