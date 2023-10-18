#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "Project_Steel/Ships/ShipPiece.h"
#include "PlayerBuildSystem.generated.h"


class UDataTable;
class APlayerCharacter;
struct FInputActionValue;

UCLASS(Blueprintable)
class PROJECT_STEEL_API UPlayerBuildSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerBuildSystem();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	void SetUpInputs(UEnhancedInputComponent* EnhancedInputComponent);

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* ToggleBuildModeInput;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* PlacePartInput;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* RotatePreviewInput;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* ScrollPartsInput;


protected:

	UPROPERTY(EditAnywhere, Category = Building)
	UDataTable* ShipParts;

private:

	void ToggleBuildMode(const FInputActionValue& Value);
	void PlacePart(const FInputActionValue& Value);
	void StartPreviewRotation(const FInputActionValue& Value);
	void StopPreviewRotation(const FInputActionValue& Value);
	void CyclePreview(const FInputActionValue& Value);

	void PreviewLoop();
	void RotatePreview(float Value);

	FTransform DetectSockets(AShipPiece* HitShipPiece, const UPrimitiveComponent* HitComponent) const;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	bool CheckForOverlaps();
	void ResetPreviewMesh();

	UFUNCTION(Server, Unreliable)
	void ServerSpawn(FTransform SpawnTransform, UClass* ToSpawn);

private:

	bool InBuildMode;
	int ShipPartIndex;
	bool PreviewBlocked;

	UPROPERTY()
	FBox PreviewBoundingBox;

	UPROPERTY()
	FTimerHandle RotationHandle;

	UPROPERTY()
	TArray<FShipParts> ShipPartsArray;

	UPROPERTY()
	APlayerCharacter* PlayerCharacter;

	UPROPERTY()
	UStaticMeshComponent* PreviewMesh;

	UPROPERTY(EditAnywhere, Category = Building)
	UMaterial* CorrectPreviewMaterial;

	UPROPERTY(EditAnywhere, Category = Building)
	UMaterial* WrongPreviewMaterial;

	UPROPERTY()
	FTransform PreviewTransform;
};
