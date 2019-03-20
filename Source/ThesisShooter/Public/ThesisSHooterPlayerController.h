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

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SaveDataToFile();

	UPROPERTY(VisibleAnywhere)
	int32 ShotHits;
	UPROPERTY(VisibleAnywhere)
	int32 Shots;

	int32 TargetsHit;
	UPROPERTY(VisibleAnywhere)
	int32 AccuracyScore;

	UPROPERTY(VisibleAnywhere)
	float FirstSectionTime;
	float SecondSectionTime;
	float ThirdSectionTime;

	float ReactionTime;
	
	int32 GameSection;
	
	FString PlayerIndex = "123";

	TArray<float> HitTimesStaticTargets;

protected:
	virtual void SetupInputComponent() override;
	
};
