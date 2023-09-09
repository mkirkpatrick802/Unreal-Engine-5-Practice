#include "EnemyCharacter.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	_controller = Cast<AEnemyController>(GetController());
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    FString VelocityString = _controller->GetCurrentForceDirection().ToString();

    // Set up the debug message parameters
    FColor Color = FColor::White; // Text color
    float DisplayTime = 1.0f;    // Display time in seconds
    FVector2D TextScale = FVector2D(1.0f, 1.0f); // Text scale

    // Display the velocity on the screen
    GEngine->AddOnScreenDebugMessage(1, DisplayTime, Color, VelocityString, false, TextScale);

	AddMovementInput(_controller->GetCurrentForceDirection(), _wanderingConstant, true);

}