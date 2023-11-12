#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Hornet.generated.h"

class Octree;
class USphereComponent;
class UArrowComponent;

UENUM(BlueprintType)
enum HornetState
{
	Flocking = 0,	// In this state the hornet will be preforming standard flocking behavior w/ Separation, Alignment, Cohesion
	Chase,			// In this state the hornet will be chasing a target while maintaining its formation w/ Separation, Cohesion
	Fleeing,		// In this state the hornet will be moving away from players and trying to regroup with it others
};

UCLASS()
class PROJECT_STINGER_API AHornet : public APawn
{
	GENERATED_BODY()

public:

	AHornet();
	virtual void Tick(float DeltaTime) override;

	// Setters
	void SetTree(Octree* Tree);

	// Getters
	float GetColliderRadius() { return ColliderRadius; }

protected:

	virtual void BeginPlay() override;

private:

	void UpdateNeighbourhood();
	void UpdateTransform();
	void DrawDebug() const;

public:



protected:

	UPROPERTY(EditAnywhere, Category = "Boid")
	float VisionRadius;

	UPROPERTY(EditAnywhere, Category = "Boid")
	float ColliderRadius = 75;

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereCollider;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UArrowComponent* Arrow;

private:

	UPROPERTY()
	TEnumAsByte<HornetState> CurrentState;

	UPROPERTY()
	FTransform Transform;

	UPROPERTY()
	TArray<AHornet*> Neighborhood;

	UPROPERTY()
	FVector Velocity;

	// Used for finding neighbors
	Octree* HornetOctree;
};
