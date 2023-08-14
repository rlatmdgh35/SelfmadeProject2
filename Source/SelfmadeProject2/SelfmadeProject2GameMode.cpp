// Copyright Epic Games, Inc. All Rights Reserved.

#include "SelfmadeProject2GameMode.h"
#include "SelfmadeProject2Character.h"
#include "UObject/ConstructorHelpers.h"

ASelfmadeProject2GameMode::ASelfmadeProject2GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}
