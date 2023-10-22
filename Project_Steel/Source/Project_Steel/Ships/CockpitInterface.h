#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CockpitInterface.generated.h"

UINTERFACE(MinimalAPI)
class UCockpitInterface : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_STEEL_API ICockpitInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Cockpit")
	FVector GetLocalForward();

};
