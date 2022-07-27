// Copyright Epic Games, Inc. All Rights Reserved.

#include "GeneHunterGameMode.h"
#include "GeneHunterCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGeneHunterGameMode::AGeneHunterGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
