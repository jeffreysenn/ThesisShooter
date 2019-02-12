// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/ThesisSHooterPlayerController.h"

AThesisSHooterPlayerController::AThesisSHooterPlayerController()
{
	ShotHits = 0;
	Shots = 0;
	TargetsHit = 0;
	AccuracyScore = 0;
	GameSection = 1;

	FirstSectionTime = 0;
	SecondSectionTime = 0;
	ThirdSectionTime = 0;

	ReactionTime = 0;
}

void AThesisSHooterPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (GameSection)
	{
	case 1:
		FirstSectionTime += DeltaTime;
		break;
	case 2:
		SecondSectionTime += DeltaTime;
		break;
	case 3:
		ThirdSectionTime += DeltaTime;
		break;
	}
	

}
