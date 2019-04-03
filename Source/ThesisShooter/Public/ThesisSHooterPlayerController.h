// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ThesisSHooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class THESISSHOOTER_API AThesisSHooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AThesisSHooterPlayerController();

	class UC_ThesisGameInstance * ThesisGameInstance;
	
	virtual void BeginPlay();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SaveDataToFile();

	
protected:
	virtual void SetupInputComponent() override;
	
};
