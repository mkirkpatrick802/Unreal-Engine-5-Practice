#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "Project_Steel/Ships/ShipPiece.h"
#include "PlayerBuildSystem.generated.h"


class UInputAction;
class UDataTable;
class APlayerCharacter;
struct FInputActionValue;

UCLASS(Blueprintable)
class PROJECT_STEEL_API UPlayerBuildSystem : public UActorComponent
{
	GENERATED_BODY()

public:

	UPlayerBuildSystem();
	void SetUpInputs(UEnhancedInputComponent* EnhancedInputComponent);
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	virtual void BeginPlay() override;

private:

	void ToggleBuildMode(const FInputActionValue& Value);
	void PlacePart(const FInputActionValue& Value);
	void StartPreviewRotation(const FInputActionValue& Value);
	void StopPreviewRotation(const FInputActionValue& Value);
	void CyclePreview(const FInputActionValue& Value);

	void PreviewLoop();
	void RotatePreview(float Value);

	FTransform DetectSockets(AShipPiece* HitShipPiece, const UPrimitiveComponent* HitComponent);
	void ResetPreviewMesh();

	UFUNCTION(Server, Unreliable)
	void ServerSpawn(FTransform SpawnTransform, UClass* ToSpawn);


protected:

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* ToggleBuildModeInput;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* PlacePartInput;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* RotatePreviewInput;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* ScrollPartsInput;

	UPROPERTY(EditAnywhere, Category = Building)
	UDataTable* ShipParts;

private:

	UPROPERTY()
	APlayerCharacter* PlayerCharacter;

	UPROPERTY()
	UStaticMeshComponent* PreviewMesh;

	UPROPERTY()
	TArray<FShipParts> ShipPartsArray;

	UPROPERTY()
	FTransform PreviewTransform;

	UPROPERTY()
	FTimerHandle RotationHandle;

	UPROPERTY()
	FRotator SocketRotation;

	UPROPERTY()
	AActor* SocketShip;

	UPROPERTY(EditAnywhere, Category = Building)
	UMaterial* CorrectPreviewMaterial;

	UPROPERTY(EditAnywhere, Category = Building)
	UMaterial* WrongPreviewMaterial;

	bool InBuildMode;
	int ShipPartIndex;
	bool PreviewBlocked;
	bool PreviewLockedInSocket;
};
