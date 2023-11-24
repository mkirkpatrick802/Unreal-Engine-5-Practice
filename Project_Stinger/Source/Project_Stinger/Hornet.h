#pragma once

#include "CoreMinimal.h"
#include "BulletHitInterface.h"
#include "HornetController.h"
#include "InteractWithCrosshairsInterface.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "Hornet.generated.h"

class UAISenseConfig_Sight;
class UAIPerceptionComponent;
class Octree;
class USphereComponent;
class UArrowComponent;

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
	float GetColliderRadius() const { return SphereCollider->GetUnscaledSphereRadius(); }
	float GetVisionRadius() const { return VisionRadius; }

protected:

	virtual void BeginPlay() override;

private:

	void CalculateNewMoveVector();
	void ResetForces();
	void CalculateAlignment();
	void CalculateCohesion();
	void CalculateSeparation();
	void CalculateCollisions();
	void CalculateRandomMoveVector();

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
	float VisionRadius = 300;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 600;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxSpeed = 800;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxRotationSpeed = 6;

	/**
	 *	Alignment Settings
	 */

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float AlignmentRadius = 300;

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float AlignmentWeight = .5f;

	/**
	 *	Cohesion Settings
	 */

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float CohesionRadius = 150;

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float CohesionWeight = 1;

	/**
	 *	Separation Settings
	 */

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float SeparationRadius = 100;

	UPROPERTY(EditAnywhere, Category = "Flocking", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float SeparationWeight = 3;

	float SeparationWeightScale = 20;

private:

	FTransform Transform;

	Octree* HornetOctree;
	TArray<AHornet*> Neighborhood;

	FVector CohesionForce;
	FVector AlignmentForce;
	FVector SeparationForce;
	FVector CollisionForce;
	FVector NewMoveVector;
};
