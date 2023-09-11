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
	FVector dir = _controller->GetCurrentForceDirection();

	if(!IsCharacterLeavingNavmesh())
	{
		dir.X *= -1;
		dir.Y *= -1;
	}

	AddMovementInput(dir, _wanderingConstant, true);
}

bool AEnemyCharacter::IsCharacterLeavingNavmesh()
{
	FNavLocation navLoc;
	FVector queryExtent = FVector(50, 50, 250);
	FNavAgentProperties navAgentProperties;
	navAgentProperties.AgentHeight = 180;
	navAgentProperties.AgentRadius = 40;

	UNavigationSystemV1* NavSystem = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());

	return NavSystem->ProjectPointToNavigation(GetActorLocation(), navLoc, queryExtent);
}
