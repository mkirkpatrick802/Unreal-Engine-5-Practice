#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "StingerHUD.generated.h"

USTRUCT(BlueprintType)
struct FHUDPackage
{
	GENERATED_BODY()

public:

	class UTexture2D* CrosshairsCenter;
	class UTexture2D* CrosshairsLeft;
	class UTexture2D* CrosshairsRight;
	class UTexture2D* CrosshairsTop;
	class UTexture2D* CrosshairsBottom;
};

UCLASS()
class PROJECT_STINGER_API AStingerHUD : public AHUD
{
	GENERATED_BODY()

public:

	virtual void DrawHUD() override;

private:

	void DrawCrosshair(UTexture2D* Texture, FVector2D ViewportCenter);

public:

	FORCEINLINE void SetHUDPackage(const FHUDPackage& Package) { HUDPackage = Package; }

private:

	FHUDPackage HUDPackage;
};
