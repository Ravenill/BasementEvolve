// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BasementEvolveGameMode.h"
#include "BasementEvolvePlayerController.h"
#include "BasementEvolveCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABasementEvolveGameMode::ABasementEvolveGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ABasementEvolvePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}