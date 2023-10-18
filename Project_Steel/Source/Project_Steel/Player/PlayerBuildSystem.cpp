#include "PlayerBuildSystem.h"

#include "EnhancedInputComponent.h"
#include "PlayerCharacter.h"
#include "Engine/DataTable.h"
#include "Project_Steel/Ships/ShipPieceInterface.h"

#define ECC_BuildPreview ECC_GameTraceChannel1
#define ECC_BuildSocket ECC_GameTraceChannel2
#define ECC_ShipPiece ECC_GameTraceChannel3
#define ECC_Buildable ECC_GameTraceChannel4

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
		if(PreviewLockedInSocket)
		{
			SocketRotation.Yaw += 90 * Value.Get<float>();
		}
		else
		{
			const FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &UPlayerBuildSystem::RotatePreview, Value.Get<float>());
			PlayerCharacter->GetWorldTimerManager().SetTimer(RotationHandle, TimerDelegate, 0.01f, true);
		}
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
	ECollisionChannel TraceChannel = ECC_Buildable;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredComponent(PreviewMesh);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, TraceChannel, CollisionParams))
	{
		AActor* HitActor = HitResult.GetActor();

		if (!PreviewMesh)
		{
			ResetPreviewMesh();
		}

		TArray<AActor*> OverlappingActors;
		PreviewMesh->GetOverlappingActors(OverlappingActors);
		if (OverlappingActors.Num() < 1)
			PreviewBlocked = false;
		else
			PreviewBlocked = true;

		if (HitActor->IsA(AShipPiece::StaticClass()))
		{
			AShipPiece* ShipPiece = Cast<AShipPiece>(HitActor);
			PreviewTransform = DetectSockets(ShipPiece, HitResult.GetComponent());
			PreviewTransform.SetRotation((PreviewTransform.GetRotation().Rotator() + SocketRotation).Quaternion());
			PreviewMesh->SetWorldTransform(PreviewTransform);
			PreviewLockedInSocket = true;
		}
		else
		{
			FVector NewPosition = FVector(HitResult.Location.X, HitResult.Location.Y, -90);
			PreviewTransform.SetLocation(NewPosition);
			PreviewTransform.SetRotation(PreviewTransform.GetRotation());
			PreviewMesh->SetWorldTransform(PreviewTransform);
			PreviewLockedInSocket = false;
		}

		if(PreviewBlocked)
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
	const FRotator NewRotation = Change + PreviewTransform.Rotator();
	PreviewTransform.SetRotation(NewRotation.Quaternion());
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

void UPlayerBuildSystem::ResetPreviewMesh()
{
	USceneComponent* RootComponent = NewObject<USceneComponent>(this, USceneComponent::StaticClass(), TEXT("Preview"));
	PreviewMesh = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(), TEXT("Preview Mesh"));
	if(PreviewMesh && RootComponent)
	{
		PreviewMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		PreviewMesh->RegisterComponent();
		PreviewMesh->SetMaterial(0, CorrectPreviewMaterial);
		PreviewMesh->SetRelativeTransform(PreviewTransform);
		PreviewMesh->SetStaticMesh(ShipPartsArray[ShipPartIndex].Mesh);
		PreviewMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		PreviewMesh->SetCollisionObjectType(ECC_BuildPreview);
		PreviewMesh->SetGenerateOverlapEvents(true);
	}
}

void UPlayerBuildSystem::ServerSpawn_Implementation(const FTransform SpawnTransform, UClass* ToSpawn)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = nullptr;

	GetWorld()->SpawnActor<AShipPiece>(ToSpawn, SpawnTransform, SpawnParams);
}
