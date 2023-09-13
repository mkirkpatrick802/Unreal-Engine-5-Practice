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

void AEnemyController::Flocking(const TArray<AActor*>& c_neighbours, int c_length, const TArray<AActor*>& s_neighbours, int s_length)
{
    cohesionDirection = FVector(0, 0, 0);
    alignmentDirection = FVector(0, 0, 0);
    separationDirection = FVector(0, 0, 0);

    if(cohesionConstant != 0)
		CalculateCohesionDirection(c_neighbours, c_length);

    if (alignmentConstant != 0)
		CalculateAlignmentDirection(c_neighbours, c_length);

    if (separationConstant != 0)
		CalculateSeperationDirection(s_neighbours, s_length);
}

void AEnemyController::CalculateSeperationDirection(const TArray<AActor*>& neighbours, int length)
{
    FVector force;
    for (auto i = 0; i < length; ++i)
    {
        force += this->GetPawn()->GetActorLocation() - neighbours[i]->GetActorLocation();
    }

    if(!force.Normalize())
    {
        force *= 100;
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
        averageVelocity += neighbours[i]->GetVelocity();
    }
    averageVelocity += GetCharacter()->GetVelocity();

    averageVelocity = averageVelocity / length + 1;
    alignmentDirection = averageVelocity;
}

void AEnemyController::SetConstant(EConstantTypes type, float value)
{
	switch (type) {
	case Wandering:
        wanderingConstant = value;
		break;
	case Seperation:
        separationConstant = value;
		break;
	case Cohesion:
        cohesionConstant = value;
		break;
	case Alignment:
        alignmentConstant = value;
		break;
	default: ;
	}
}