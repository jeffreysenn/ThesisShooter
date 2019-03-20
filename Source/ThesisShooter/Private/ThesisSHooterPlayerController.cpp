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
	FString DataContent = FString("Participant: " + PlayerIndex + LINE_TERMINATOR
		+ "Shots that hit target: " + FString::FromInt(ShotHits) + LINE_TERMINATOR
		+ "Total Shots fired: " + FString::FromInt(Shots) + LINE_TERMINATOR
		//+ "Amount of Targets hit: " +  FString::FromInt(TargetsHit) + LINE_TERMINATOR
		+ "Accuracy score: " + FString::FromInt(AccuracyScore) + LINE_TERMINATOR
		+ LINE_TERMINATOR
		+ "First section time: " + FString::SanitizeFloat(FirstSectionTime) + LINE_TERMINATOR
		+ "Second section time: "+ FString::SanitizeFloat(SecondSectionTime) + LINE_TERMINATOR
		+ "Third section time: " + FString::SanitizeFloat(ThirdSectionTime) + LINE_TERMINATOR
		+"Total time: " + FString::SanitizeFloat(FirstSectionTime + SecondSectionTime + ThirdSectionTime) + LINE_TERMINATOR 
		+ "Hit Times On Static Targets: " + LINE_TERMINATOR);

	
	if (HitTimesStaticTargets.Num())
	{
		for (int32 i = 0; i < HitTimesStaticTargets.Num(); i++)
		{
			DataContent += FString("" + FString::SanitizeFloat(HitTimesStaticTargets[i]) + LINE_TERMINATOR);
		}
	}

	DataContent += FString(+LINE_TERMINATOR);

	FString FilePath = FPaths::ConvertRelativePathToFull(FPaths::GameSavedDir()) + TEXT("/DataLog"+ PlayerIndex +".txt");
	FString FileContent = TEXT(""+DataContent);
	FFileHelper::SaveStringToFile(FileContent, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);

}


