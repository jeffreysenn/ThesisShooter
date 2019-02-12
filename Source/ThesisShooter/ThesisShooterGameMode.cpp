// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ThesisShooterGameMode.h"
#include "ThesisShooterHUD.h"
#include "ThesisShooterCharacter.h"
#include "UObject/ConstructorHelpers.h"

AThesisShooterGameMode::AThesisShooterGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AThesisShooterHUD::StaticClass();
}
