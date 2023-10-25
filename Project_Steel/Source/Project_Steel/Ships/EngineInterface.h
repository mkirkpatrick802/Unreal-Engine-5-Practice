#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EngineInterface.generated.h"

UINTERFACE(MinimalAPI)
class UEngineInterface : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_STEEL_API IEngineInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Engines")
	FVector GetPushVector();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Engines")
	float GetForce();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Engines")
	UMaterial* GetFirstMaterial();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Engines")
	UMaterial* GetSecondMaterial();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Engines")
	void ToggleMaterial(bool UseSecondary);

};