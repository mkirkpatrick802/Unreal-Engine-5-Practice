#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerBuildSystem.generated.h"


UCLASS(Blueprintable)
class PROJECT_STEEL_API UPlayerBuildSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerBuildSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
