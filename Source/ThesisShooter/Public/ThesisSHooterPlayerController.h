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

	UPROPERTY(VisibleAnywhere)
	int ShotHits;
	UPROPERTY(VisibleAnywhere)
	int Shots;

	int TargetsHit;
	UPROPERTY(VisibleAnywhere)
	int AccuracyScore;

	float FirstSectionTime;
	float SecondSectionTime;
	float ThirdSectionTime;

	float ReactionTime;
};
