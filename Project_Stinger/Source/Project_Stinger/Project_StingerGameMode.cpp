// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_StingerGameMode.h"
#include "Project_StingerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProject_StingerGameMode::AProject_StingerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
