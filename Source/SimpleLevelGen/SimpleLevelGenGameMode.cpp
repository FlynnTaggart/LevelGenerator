// Copyright Epic Games, Inc. All Rights Reserved.

#include "SimpleLevelGenGameMode.h"
#include "SimpleLevelGenCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASimpleLevelGenGameMode::ASimpleLevelGenGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
