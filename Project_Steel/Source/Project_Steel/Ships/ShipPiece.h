// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "ShipPiece.generated.h"

class APlayerCharacter;
class AShip;

USTRUCT(BlueprintType)
struct FShipParts : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UClass* Blueprint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ETraceTypeQuery> LayerTracChannel;
};

UCLASS()
class PROJECT_STEEL_API AShipPiece : public AActor
{
	GENERATED_BODY()
	
public:	

	AShipPiece();
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:

	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintNativeEvent)
	void Interact(APlayerCharacter* Player);

	UFUNCTION(BlueprintNativeEvent)
	void Placed();

	UFUNCTION(BlueprintCallable)
	void ConfigurePiece();

private:

	void CreateNewShip();

public:

	UFUNCTION(Server, Unreliable)
	void ServerSpawnShipParent(const FTransform SpawnTransform, UClass* ToSpawn);

public:

	UPROPERTY(BlueprintReadOnly, Replicated)
	AShip* Ship;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComponent;

};
