#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "UObject/Interface.h"
#include "ShipPieceInterface.generated.h"

UINTERFACE(MinimalAPI)
class UShipPieceInterface : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_STEEL_API IShipPieceInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Sockets")
	TArray<UBoxComponent*> GetSockets();
};
