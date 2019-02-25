// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ThesisShooterGameMode.h"
#include "ThesisShooterHUD.h"
#include "ThesisShooterCharacter.h"
#include "UObject/ConstructorHelpers.h"

AThesisShooterGameMode::AThesisShooterGameMode()
	: Super()
{

	// use our custom HUD class
	HUDClass = AThesisShooterHUD::StaticClass();
}
