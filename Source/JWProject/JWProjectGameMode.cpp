// Copyright Epic Games, Inc. All Rights Reserved.

#include "JWProjectGameMode.h"
#include "JWProjectHUD.h"
#include "JWProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AJWProjectGameMode::AJWProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AJWProjectHUD::StaticClass();
}
