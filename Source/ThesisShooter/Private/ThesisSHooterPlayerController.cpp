// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/ThesisSHooterPlayerController.h"
#include "FileHelper.h"
#include "Paths.h"

AThesisSHooterPlayerController::AThesisSHooterPlayerController()
{
	ShotHits = 0;
	Shots = 0;
	TargetsHit = 0;
	AccuracyScore = 0;
	GameSection = 0;

	FirstSectionTime = 0;
	SecondSectionTime = 0;
	ThirdSectionTime = 0;

	ReactionTime = 0;
}

void AThesisSHooterPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UE_LOG(LogTemp, Warning, TEXT("@SetupInputComponent was called in player controller "));
	this->InputComponent->BindAction("SaveData", EInputEvent::IE_Pressed, this, &AThesisSHooterPlayerController::SaveDataToFile);
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
void AThesisSHooterPlayerController::SaveDataToFile()
{

	UE_LOG(LogTemp, Warning, TEXT("@SaveDataToFile saving data to file "));

	FString FilePath = FPaths::ConvertRelativePathToFull(FPaths::GameSavedDir()) + TEXT("/DataLog"+ PlayerIndex +".txt");
	FString FileContent = TEXT("This is a line of text to put in the file.\n");
	FFileHelper::SaveStringToFile(FileContent, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);

}


