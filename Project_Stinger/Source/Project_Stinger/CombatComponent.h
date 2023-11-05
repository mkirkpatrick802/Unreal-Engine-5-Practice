#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_STINGER_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()
	friend class AStingerCharacter;

public:	

	UCombatComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:

	virtual void BeginPlay() override;
	void ToggleAiming();

	UFUNCTION(Server, Reliable)
	void ServerSetAiming(bool Aiming);

	void Fire();

private:

	class AStingerCharacter* Character;

	UPROPERTY(Replicated)
	bool IsAiming;

public:	

};