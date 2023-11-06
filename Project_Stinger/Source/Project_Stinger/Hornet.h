#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Hornet.generated.h"

UCLASS()
class PROJECT_STINGER_API AHornet : public APawn
{
	GENERATED_BODY()

public:

	AHornet();
	virtual void Tick(float DeltaTime) override;


protected:

	virtual void BeginPlay() override;

private:

	void UpdateNeighbourhood();
	void UpdateTransform();

public:

protected:

	UPROPERTY(EditAnywhere, Category = "Boid")
	float VisionRadius;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;

private:

	UPROPERTY()
	FTransform Transform;

	UPROPERTY()
	TArray<AHornet*> Neighborhood;

};
