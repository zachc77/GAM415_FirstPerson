// Copyright Epic Games, Inc. All Rights Reserved.

#include "GAM415_firstpersonGameMode.h"
#include "GAM415_firstpersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGAM415_firstpersonGameMode::AGAM415_firstpersonGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
