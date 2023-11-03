#include "LobbyGameMode.h"

#include "GameFramework/GameStateBase.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	int NumberOfPlayers = GameState.Get()->PlayerArray.Num();
	if(NumberOfPlayers == 4)
	{
		UWorld* World = GetWorld();
		if(World)
		{
			bUseSeamlessTravel = true;
			World->ServerTravel(FString("/Game/Project_Stinger/Maps/StingerMap?listen"));
		}
	}
}
