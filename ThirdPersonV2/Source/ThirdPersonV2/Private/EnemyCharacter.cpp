#include "EnemyCharacter.h"
#include "NavigationSystem.h"

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

	if (!_controller) return;
	Move();
}

void AEnemyCharacter::Move()
{
	FVector randomDir = _controller->GetCurrentForceDirection();

	if(IsCharacterLeavingNavmesh() || _atBorder)
	{
		FVector originDir = FVector(0, 0, 0) - GetActorLocation();
		AddMovementInput(originDir, _controller->wanderingConstant, true);
	}
	else
	{
		/*if (EnemyState.GetValue() == EEnemyState::Wander)
			AddMovementInput(randomDir, _controller->wanderingConstant, true);
		else
		{
			//Seperation
			AddMovementInput(_controller->separationDirection, _controller->separationConstant, true);

			//Cohesion
			//AddMovementInput(_controller->cohesionDirection, _controller->cohesionConstant, true);

			//Alignment
			//AddMovementInput(_controller->alignmentDirection, _controller->alignmentConstant, true);
		}*/
	}
}

bool AEnemyCharacter::IsCharacterLeavingNavmesh()
{
	FNavLocation navLoc;
	FVector queryExtent = FVector(50, 50, 250);
	FNavAgentProperties navAgentProperties;
	navAgentProperties.AgentHeight = 180;
	navAgentProperties.AgentRadius = 40;

	UNavigationSystemV1* NavSystem = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());
	if(!NavSystem->ProjectPointToNavigation(GetActorLocation(), navLoc, queryExtent))
	{
		_atBorder = true;
		StartReturnCooldown();
		return true;
	}
	else
	{
		return false;
	}
}

void AEnemyCharacter::StartReturnCooldown()
{
	float cooldownTime = 2;
	FTimerHandle TimerHandle;

	GetWorldTimerManager().SetTimer(TimerHandle, [this]() {

		_atBorder = false;

		}, cooldownTime, false);
}
