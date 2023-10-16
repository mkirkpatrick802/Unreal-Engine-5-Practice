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

	//Building Inputs
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* ToggleBuildModeInput;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* PlaceInput;

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
	void RotatePreview(const FInputActionValue& Value);
	void SelectPreview(const FInputActionValue& Value);

	void PreviewLoop();
	void ResetBuildMode();

	UFUNCTION(Server, Unreliable)
	void ServerSpawn(FTransform SpawnTransform, UClass* ToSpawn);

private:

	bool InBuildMode;

	UPROPERTY()
	TArray<FShipParts> ShipPartsArray;

	UPROPERTY()
	APlayerCharacter* PlayerCharacter;

	UPROPERTY()
	UStaticMesh* PreviewMesh;

	UPROPERTY()
	UStaticMeshComponent* StaticMeshComponent;
};
