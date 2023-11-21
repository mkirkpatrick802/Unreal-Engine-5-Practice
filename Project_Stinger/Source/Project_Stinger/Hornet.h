#pragma once

#include "CoreMinimal.h"
#include "BulletHitInterface.h"
#include "InteractWithCrosshairsInterface.h"
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

/**
 *	Hornet Boid
 */
UCLASS()
class PROJECT_STINGER_API AHornet : public APawn, public IInteractWithCrosshairsInterface, public IBulletHitInterface
{
	// Object Init & Components
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereCollider;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UArrowComponent* Arrow;

public:

	AHornet();
	virtual void Tick(float DeltaTime) override;
	virtual void Hit() override;
	virtual void Destroyed() override;

	// Setters
	FORCEINLINE void SetTree(Octree* Tree) { HornetOctree = Tree; }

	// Getters
	float GetColliderRadius() const { return ColliderRadius; }
	float GetVisionRadius() const { return VisionRadius; }

protected:

	virtual void BeginPlay() override;

private:

	void CalculateNewMoveVector();
	void ResetForces();
	void CalculateAlignment();
	void CalculateCohesion();
	void CalculateSeparation();

	void UpdateNeighbourhood();
	void UpdateTransform(float DeltaTime);


	void DrawDebug() const;

public:

	UPROPERTY()
	FVector CurrentMoveVector;

protected:

	/**
	 *	General Settings
	 */

	UPROPERTY(EditAnywhere, Category = "Boid")
	float VisionRadius = 200;

	UPROPERTY(EditAnywhere, Category = "Boid")
	float ColliderRadius = 100;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 40;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxSpeed = 100;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxRotationSpeed = 3;

	/**
	 *	Alignment Settings
	 */

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float AlignmentWeight = .1f;

	/**
	 *	Cohesion Settings
	 */

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float CohesionWeight = .5f;

	// Damping
	UPROPERTY(EditAnywhere, Category = "Flocking")
	float CohesionLerp = 5;

	/**
	 *	Separation Settings
	 */

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float SeparationWeight = 1000;

	// Damping
	UPROPERTY(EditAnywhere, Category = "Flocking")
	float SeparationLerp = 5;

private:

	UPROPERTY()
	TEnumAsByte<HornetState> CurrentState;

	UPROPERTY()
	FTransform Transform;

	UPROPERTY()
	TArray<AHornet*> Neighborhood;

	UPROPERTY()
	FVector CohesionForce;

	UPROPERTY()
	FVector AlignmentForce;

	UPROPERTY()
	FVector SeparationForce;

	UPROPERTY()
	FVector NewMoveVector;

	Octree* HornetOctree;
};
