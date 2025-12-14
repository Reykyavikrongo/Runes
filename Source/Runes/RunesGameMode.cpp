// Copyright Epic Games, Inc. All Rights Reserved.

#include "RunesGameMode.h"
#include "RunesCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARunesGameMode::ARunesGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
