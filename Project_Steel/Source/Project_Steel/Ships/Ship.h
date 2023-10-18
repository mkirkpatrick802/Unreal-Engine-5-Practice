// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ship.generated.h"

class AShipPiece;

UCLASS()
class PROJECT_STEEL_API AShip : public AActor
{
	GENERATED_BODY()
	
public:

	AShip();
	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;
};
