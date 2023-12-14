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

typedef void (AHornet::*ActionFunction)();

UCLASS()
class PROJECT_STINGER_API AHornet : public APawn, public IInteractWithCrosshairsInterface, public IBulletHitInterface
{
	// Object Init & Components
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereCollider;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* Mesh;

public:

	AHornet();
	virtual void Tick(float DeltaTime) override;
	virtual void Hit() override;
	virtual void Destroyed() override;

	// Setters
	FORCEINLINE void SetTree(Octree* Tree) const { HornetController->SetTree(Tree); }
	FORCEINLINE void SetNeighborhood(const TArray<AHornet*>& NewNeighborhood) { Neighborhood = NewNeighborhood; }

	// Getters
	FORCEINLINE void GetNeighborhood(TArray<AHornet*>& Neighbors) const { Neighbors = Neighborhood; }
	FORCEINLINE float GetColliderRadius() const { return SphereCollider->GetUnscaledSphereRadius(); }
	FORCEINLINE float GetVisionRadius() const { return VisionRadius; }

protected:

	virtual void BeginPlay() override;

	//State & Action Updates
	UFUNCTION()
	FORCEINLINE void OnHornetActionUpdated(HornetActions NewAction) { CurrentAction = NewAction; }

	UFUNCTION()
	FORCEINLINE void OnHornetStateUpdated(HornetStates NewState) { CurrentState = NewState; }

private:

	void CalculateNewMoveVector();
	void ResetForces();
	void CalculateAlignment();
	void CalculateCohesion();
	void CalculateSeparation();
	void CalculateVariance();

	void UpdateTransform(float DeltaTime);

	// Action Behaviors
	void Wander();
	void Swarm();
	void Flock();
	void Charge();
	void Chase();
	void Flee();

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
	float MaxSpeedVariance = 50;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxRotationSpeed = 6;

	//Swarm

	UPROPERTY(EditAnywhere, Category = "Swarm")
	float SwarmAlignmentRadius = 1500;

	UPROPERTY(EditAnywhere, Category = "Swarm")
	float SwarmAlignmentWeight = 15;

	UPROPERTY(EditAnywhere, Category = "Swarm")
	float SwarmCohesionRadius = 1500;

	UPROPERTY(EditAnywhere, Category = "Swarm")
	float SwarmCohesionWeight = 500;

	UPROPERTY(EditAnywhere, Category = "Swarm")
	float SwarmSeparationRadius = 600;

	UPROPERTY(EditAnywhere, Category = "Swarm")
	float SwarmSeparationWeight = 3000;

	UPROPERTY(EditAnywhere, Category = "Swarm")
	float SwarmVarianceWeight = 700;

	UPROPERTY(EditAnywhere, Category = "Swarm")
	float SwarmResistanceToChange = 300;

	UPROPERTY(EditAnywhere, Category = "Swarm")
	float SwarmAvoidanceWeight = 1000;

	//Flocking

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float FlockingAlignmentRadius = 1500;

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float FlockingAlignmentWeight = 15;

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float FlockingCohesionRadius = 1500;

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float FlockingCohesionWeight = 500;

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float FlockingSeparationRadius = 600;

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float FlockingSeparationWeight = 3000;

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float FlockingVarianceWeight = 700;

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float FlockingResistanceToChange = 300;

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float FlockingAvoidanceWeight = 1000;

	
	float AlignmentRadius = 1500;
	float AlignmentWeight = 15;
	float CohesionRadius = 1500;
	float CohesionWeight = 500;
	float SeparationRadius = 600;
	float SeparationWeight = 3000;
	float VarianceWeight = 700;
	float ResistanceToChange = 300;
	float AvoidanceWeight = 1000;

private:

	UPROPERTY()
	AHornetController* HornetController;

	FTransform Transform;

	TArray<AHornet*> Neighborhood;

	TEnumAsByte<HornetStates> CurrentState;
	TEnumAsByte<HornetActions> CurrentAction;
	TMap<HornetActions, ActionFunction> ActionFunctionMap;

	FVector CohesionForce;
	FVector AlignmentForce;
	FVector SeparationForce;
	FVector VarianceForce;
	FVector AvoidanceForce;
	FVector NewMoveVector;
};
