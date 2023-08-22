// Copyright Epic Games, Inc. All Rights Reserved.

#include "SelfmadeProject2GameMode.h"
#include "Player/C_Player.h"
#include "UObject/ConstructorHelpers.h"

ASelfmadeProject2GameMode::ASelfmadeProject2GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Player/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}
