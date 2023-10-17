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

	EnhancedInputComponent->BindAction(ScrollPartsInput, ETriggerEvent::Started, this, &UPlayerBuildSystem::CyclePreview);
}

void UPlayerBuildSystem::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(this->GetOwner());
}

void UPlayerBuildSystem::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
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

		for (const auto& Element : RowMap)
		{
			const FName RowName = Element.Key;

			if (const FShipParts* Part = ShipParts->FindRow<FShipParts>(RowName, FString()))
			{
				ShipPartsArray.Add(*Part);
			}
		}
	}
	else
	{
		if (PreviewMesh)
		{
			PreviewMesh->DestroyComponent();
			PreviewMesh = nullptr;
		}
	}
}

void UPlayerBuildSystem::PlacePart(const FInputActionValue& Value)
{
	if(!InBuildMode) return;
	if(PreviewBlocked) return;

	UClass* ActorClass = ShipPartsArray[ShipPartIndex].Blueprint;
	ServerSpawn(PreviewTransform, ActorClass);
}

void UPlayerBuildSystem::StartPreviewRotation(const FInputActionValue& Value)
{
	if (!InBuildMode) return;

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
	if (!InBuildMode) return;

	PlayerCharacter->GetWorldTimerManager().ClearTimer(RotationHandle);
}

void UPlayerBuildSystem::CyclePreview(const FInputActionValue& Value)
{
	if(!InBuildMode) return;

	ShipPartIndex += static_cast<int>(Value.Get<float>());
	ShipPartIndex = FMath::Clamp(ShipPartIndex, 0, ShipPartsArray.Num() - 1);

	if(PreviewMesh)
	{
		PreviewMesh->DestroyComponent();
		PreviewMesh = nullptr;
		ResetPreviewMesh();
	}
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
			AShipPiece* ShipPiece = Cast<AShipPiece>(HitActor);
			PreviewTransform = DetectSockets(ShipPiece, HitResult.GetComponent());
			PreviewMesh->SetWorldTransform(PreviewTransform);
		}
		else
		{
			FVector NewPosition = FVector(HitResult.Location.X, HitResult.Location.Y, -90);
			PreviewTransform.SetLocation(NewPosition);
			PreviewTransform.SetRotation(PreviewRotation.Quaternion());
			PreviewMesh->SetWorldTransform(PreviewTransform);
		}

		if(CheckForOverlaps())
		{
			PreviewMesh->SetMaterial(0, WrongPreviewMaterial);
		}
		else
		{
			PreviewMesh->SetMaterial(0, CorrectPreviewMaterial);
		}
	}
}

void UPlayerBuildSystem::RotatePreview(const float Value)
{
	const FRotator Change = FRotator(0, 1.5f, 0) * Value;
	PreviewRotation = Change + PreviewTransform.Rotator();
}

FTransform UPlayerBuildSystem::DetectSockets(AShipPiece* HitShipPiece, const UPrimitiveComponent* HitComponent) const
{
	const IShipPieceInterface* Interface = Cast<IShipPieceInterface>(HitShipPiece);
	TArray<UBoxComponent*> Sockets = Interface->Execute_GetSockets(HitShipPiece);
	for (const auto Element : Sockets)
	{
		if(Element == HitComponent)
		{
			break;
		}
	}

	return HitComponent->GetComponentTransform();
}

bool UPlayerBuildSystem::CheckForOverlaps()
{
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;

	const FBox BoundingBox = PreviewMesh->CalcBounds(PreviewTransform).GetBox();
	DrawDebugBox(GetWorld(), BoundingBox.GetCenter(), BoundingBox.GetExtent() / 1.1f, FColor::White);
	PreviewBlocked = GetWorld()->SweepSingleByObjectType(HitResult, BoundingBox.GetCenter(), BoundingBox.GetCenter(), FQuat(PreviewMesh->GetComponentRotation()), ECC_WorldDynamic, FCollisionShape::MakeBox(BoundingBox.GetExtent() / 1.1f), QueryParams);

	return PreviewBlocked;
}

void UPlayerBuildSystem::ResetPreviewMesh()
{
	PreviewMesh = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass());
	if(PreviewMesh)
	{
		PreviewMesh->AttachToComponent(PlayerCharacter->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		PreviewMesh->RegisterComponent();
		PreviewMesh->SetMaterial(0, CorrectPreviewMaterial);
		PreviewMesh->SetRelativeTransform(PreviewTransform);
		PreviewMesh->SetStaticMesh(ShipPartsArray[ShipPartIndex].Mesh);
		PreviewMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		PreviewMesh->SetGenerateOverlapEvents(true);
	}
}

void UPlayerBuildSystem::ServerSpawn_Implementation(const FTransform SpawnTransform, UClass* ToSpawn)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = nullptr;

	GetWorld()->SpawnActor<AShipPiece>(ToSpawn, SpawnTransform, SpawnParams);
}
