#include "EnemyController.h"

void AEnemyController::InitController()
{

}

void AEnemyController::AddForceDirection(FVector directionToBeAdded)
{
	_currentForceDirection += directionToBeAdded;
    _currentForceDirection = _currentForceDirection.GetSafeNormal();
}

void AEnemyController::Move()
{
	FVector moveVector = GetCurrentForceDirection() * _wanderingConstant;

    MoveToLocation(moveVector);

	FString VelocityString = moveVector.ToString();

    // Set up the debug message parameters
    FColor Color = FColor::White; // Text color
    float DisplayTime = 1.0f;    // Display time in seconds
    FVector2D TextScale = FVector2D(1.0f, 1.0f); // Text scale

    // Display the velocity on the screen
    GEngine->AddOnScreenDebugMessage(1, DisplayTime, Color, VelocityString, false, TextScale);
}
