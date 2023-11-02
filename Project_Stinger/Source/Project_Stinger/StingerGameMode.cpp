// Copyright Epic Games, Inc. All Rights Reserved.

#include "StingerGameMode.h"
#include "UObject/ConstructorHelpers.h"

AStingerGameMode::AStingerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Project_Stinger/Blueprints/BP_StingerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
