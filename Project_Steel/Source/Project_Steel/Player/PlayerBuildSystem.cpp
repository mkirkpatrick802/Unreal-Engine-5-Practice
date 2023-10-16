#include "PlayerBuildSystem.h"

#include "EnhancedInputComponent.h"
#include "PlayerCharacter.h"
#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"

UPlayerBuildSystem::UPlayerBuildSystem()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerBuildSystem::SetUpInputs(UEnhancedInputComponent* EnhancedInputComponent)
{
	EnhancedInputComponent->BindAction(ToggleBuildModeInput, ETriggerEvent::Started, this, &UPlayerBuildSystem::ToggleBuildMode);
}

void UPlayerBuildSystem::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(this->GetOwner());
}

void UPlayerBuildSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!InBuildMode) return;

	PreviewLoop();
}

void UPlayerBuildSystem::ToggleBuildMode(const FInputActionValue& Value)
{
	InBuildMode = !InBuildMode;

	if(InBuildMode)
	{
		TMap<FName, uint8*> RowMap = ShipParts->GetRowMap();

		for (auto& Element : RowMap)
		{
			const FName RowName = Element.Key;
			const FShipParts* Part = ShipParts->FindRow<FShipParts>(RowName, FString());

			if (Part)
			{
				ShipPartsArray.Add(*Part);
			}
		}
	}
	else
	{
		if (PreviewMesh)
		{
			StaticMeshComponent->SetStaticMesh(nullptr);
			PreviewMesh = nullptr;
			ResetBuildMode();
		}
	}
}

void UPlayerBuildSystem::PreviewLoop()
{
	FHitResult HitResult;
	FVector StartLocation;
	FVector EndLocation;
	ECollisionChannel TraceChannel = ECC_Visibility;

	if(GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, TraceChannel))
	{
		
	}
}

void UPlayerBuildSystem::ResetBuildMode()
{

}

void UPlayerBuildSystem::ServerSpawn_Implementation(FTransform SpawnTransform, UClass* ToSpawn)
{

}
