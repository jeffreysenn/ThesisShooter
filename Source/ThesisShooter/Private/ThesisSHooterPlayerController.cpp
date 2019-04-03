// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/ThesisSHooterPlayerController.h"
#include "FileHelper.h"
#include "Paths.h"
#include "ThesisShooterGameMode.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "C_ThesisGameInstance.h"

AThesisSHooterPlayerController::AThesisSHooterPlayerController()
{
	

	


}


void AThesisSHooterPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	if (Cast<UC_ThesisGameInstance>(GetWorld()->GetGameInstance()))
	{
		ThesisGameInstance = Cast<UC_ThesisGameInstance>(GetWorld()->GetGameInstance());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("@construction Failed to cast and assign  variable gmae instance to UC_ThesisGameInstance "));
	}
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

	switch (ThesisGameInstance->GameSection)
	{
	case 1:
		ThesisGameInstance->FirstSectionTime += DeltaTime;
		break;
	case 2:
		ThesisGameInstance->SecondSectionTime += DeltaTime;
		break;
	case 3:
		ThesisGameInstance->ThirdSectionTime += DeltaTime;
		break;
	}
	

}
void AThesisSHooterPlayerController::SaveDataToFile()
{
	/*Cast<UC_ThesisGameInstance>(GetWorld()->GetGameInstance())->SetGameSectionTime(1, FirstSectionTime);
	Cast<UC_ThesisGameInstance>(GetWorld()->GetGameInstance())->SetGameSectionTime(2, SecondSectionTime);
	Cast<UC_ThesisGameInstance>(GetWorld()->GetGameInstance())->SetGameSectionTime(3, ThirdSectionTime);*/
	
	Cast<UC_ThesisGameInstance>(GetWorld()->GetGameInstance())->SaveDataToFile();
	/*

	UE_LOG(LogTemp, Warning, TEXT("@SaveDataToFile saving data to file "));
	FString DataContent = FString("Participant: " + Cast<AThesisShooterGameMode>(GetWorld()->GetAuthGameMode())->GetPlayerIndex() + LINE_TERMINATOR
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
	
	DataContent += FString(+ LINE_TERMINATOR);
	FString FilePath = FPaths::ConvertRelativePathToFull(FPaths::GameSavedDir()) + TEXT("/DataLog_"+ Cast<AThesisShooterGameMode>(GetWorld()->GetAuthGameMode())->GetPlayerIndex() +".txt");
	FString FileContent = TEXT(""+DataContent);
	FFileHelper::SaveStringToFile(FileContent, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
	*/
}


