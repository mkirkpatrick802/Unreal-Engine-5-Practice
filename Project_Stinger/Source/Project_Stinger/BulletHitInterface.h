#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BulletHitInterface.generated.h"

UINTERFACE(MinimalAPI)
class UBulletHitInterface : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_STINGER_API IBulletHitInterface
{
	GENERATED_BODY()

public:

	virtual void Hit();

};
