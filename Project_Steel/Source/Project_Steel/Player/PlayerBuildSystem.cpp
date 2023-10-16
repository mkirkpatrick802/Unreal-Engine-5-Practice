#include "PlayerBuildSystem.h"

#include "EnhancedInputComponent.h"
#include "PlayerCharacter.h"
#include "Engine/DataTable.h"
#include "Project_Steel/Ships/ShipPieceInterface.h"

UPlayerBuildSystem::UPlayerBuildSystem()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerBuildSystem::SetUpInputs(UEnhancedInputComponent* EnhancedInputComponent)
{
	EnhancedInputComponent->BindAction(ToggleBuildModeInput, ETriggerEvent::Started, this, &UPlayerBuildSystem::ToggleBuildMode);
	EnhancedInputComponent->BindAction(PlacePartInput, ETriggerEvent::Started, this, &UPlayerBuildSystem::PlacePart);
	EnhancedInputComponent->BindAction(RotatePreviewInput, ETriggerEvent::Started, this, &UPlayerBuildSystem::StartPreviewRotation);
	EnhancedInputComponent->BindAction(RotatePreviewInput, ETriggerEvent::Completed, this, &UPlayerBuildSystem::StopPreviewRotation);
	EnhancedInputComponent->BindAction(RotatePreviewInput, ETriggerEvent::Canceled, this, &UPlayerBuildSystem::StopPreviewRotation);
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
			PreviewMesh = nullptr;
			ResetPreviewMesh();
		}
	}
}

void UPlayerBuildSystem::PlacePart(const FInputActionValue& Value)
{
	if(!InBuildMode) return;

	UClass* ActorClass = ShipPartsArray[ShipPartIndex].Blueprint;
	ServerSpawn(PreviewTransform, ActorClass);
}

void UPlayerBuildSystem::StartPreviewRotation(const FInputActionValue& Value)
{
	if (RotationHandle.IsValid())
	{
		StartPreviewRotation(Value);
	}
	else
	{
		const FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &UPlayerBuildSystem::RotatePreview, Value.Get<float>());
		PlayerCharacter->GetWorldTimerManager().SetTimer(RotationHandle, TimerDelegate, 0.01f, true);
	}
}

void UPlayerBuildSystem::StopPreviewRotation(const FInputActionValue& Value)
{
	PlayerCharacter->GetWorldTimerManager().ClearTimer(RotationHandle);
}

void UPlayerBuildSystem::PreviewLoop()
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCharacter->MouseWorldLocation;
	FVector EndLocation = PlayerCharacter->MouseWorldLocation + (PlayerCharacter->MouseWorldDirection * 2000);
	ECollisionChannel TraceChannel = ECC_Visibility;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, TraceChannel))
	{
		AActor* HitActor = HitResult.GetActor();

		if (!PreviewMesh)
		{
			ResetPreviewMesh();
		}

		if (HitActor->IsA(AShipPiece::StaticClass()))
		{
			//Hit a Ship Piece
			AShipPiece* ShipPiece = Cast<AShipPiece>(HitActor);
			PreviewTransform = DetectSockets(ShipPiece, HitResult.GetComponent());
			PreviewMesh->SetWorldTransform(PreviewTransform);
		}
		else
		{
			FVector NewPosition = FVector(HitResult.Location.X, HitResult.Location.Y, -90);
			PreviewTransform.SetLocation(NewPosition);
			//PreviewTransform.SetRotation(PreviewRotation.Quaternion());
			PreviewMesh->SetWorldTransform(PreviewTransform);
		}
	}
}

void UPlayerBuildSystem::RotatePreview(float Value)
{
	FRotator Change = FRotator(0, 0, 1.5f) * Value;
	PreviewRotation = Change + PreviewTransform.Rotator();
}

FTransform UPlayerBuildSystem::DetectSockets(AShipPiece* HitShipPiece, UPrimitiveComponent* HitComponent)
{
	IShipPieceInterface* Interface = Cast<IShipPieceInterface>(HitShipPiece);
	TArray<UBoxComponent*> Sockets = Interface->Execute_GetSockets(HitShipPiece);
	for (auto Element : Sockets)
	{
		if(Element == HitComponent)
		{
			break;
		}
	}

	return HitComponent->GetComponentTransform();
}

void UPlayerBuildSystem::ResetPreviewMesh()
{
	PreviewMesh = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass());
	if(PreviewMesh)
	{
		PreviewMesh->AttachToComponent(PlayerCharacter->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		PreviewMesh->RegisterComponent();

		PreviewMesh->SetRelativeTransform(PreviewTransform);
		PreviewMesh->SetStaticMesh(ShipPartsArray[ShipPartIndex].Mesh);
		PreviewMesh->SetMaterial(0, PreviewMaterial);
		PreviewMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void UPlayerBuildSystem::ServerSpawn_Implementation(FTransform SpawnTransform, UClass* ToSpawn)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = nullptr;

	GetWorld()->SpawnActor<AShipPiece>(ToSpawn, SpawnTransform, SpawnParams);
}
