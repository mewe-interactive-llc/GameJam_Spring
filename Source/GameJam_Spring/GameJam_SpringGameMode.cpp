// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "GameJam_SpringGameMode.h"
#include "GameJam_SpringCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGameJam_SpringGameMode::AGameJam_SpringGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
