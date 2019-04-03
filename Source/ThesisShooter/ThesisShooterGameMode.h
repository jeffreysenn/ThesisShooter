// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ThesisShooterGameMode.generated.h"

UCLASS(minimalapi)
class AThesisShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AThesisShooterGameMode();

	

	UFUNCTION(BlueprintCallable)
	void SetPlayerIndex(FString TextToSet);

	FString GetPlayerIndex();

private:
	FString PlayerIndex;
};



