// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipPiece.h"

#include "Ship.h"

// Sets default values
AShipPiece::AShipPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AShipPiece::BeginPlay()
{
	Super::BeginPlay();

	if(!Ship)
	{
		Ship = GetWorld()->SpawnActor<AShip>(GetActorLocation(), GetActorRotation());
		if(AttachToActor(Ship, FAttachmentTransformRules::SnapToTargetNotIncludingScale))
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(
					-1,
					15.f,
					FColor::Green,
					FString::Printf(TEXT("Good"))
				);
			}
		}
	}
}

// Called every frame
void AShipPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}