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

	DECLARE_DELEGATE(FHornetActionDelegate);

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
	FORCEINLINE void SetTree(Octree* Tree) const { Cast<AHornetController>(GetController())->SetTree(Tree); }
	FORCEINLINE void SetNeighborhood(const TArray<AHornet*>& NewNeighborhood) { Neighborhood = NewNeighborhood; }

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
	float VisionRadius = 7500;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 600;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxSpeed = 350;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxRotationSpeed = 6;

	/**
	 *	Alignment Settings
	 */

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float AlignmentRadius = 1500;

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float AlignmentWeight = 15;

	/**
	 *	Cohesion Settings
	 */

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float CohesionRadius = 1500;

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float CohesionWeight = 500;

	/**
	 *	Separation Settings
	 */

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float SeparationRadius = 600;

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float SeparationWeight = 3000;


private:

	FTransform Transform;

	TArray<AHornet*> Neighborhood;

	TEnumAsByte<HornetStates> CurrentState;
	TEnumAsByte<HornetActions> CurrentAction;
	TMap<HornetActions, FHornetActionDelegate> ActionFunctionMap;

	FVector CohesionForce;
	FVector AlignmentForce;
	FVector SeparationForce;
	FVector CollisionForce;
	FVector NewMoveVector;
};
