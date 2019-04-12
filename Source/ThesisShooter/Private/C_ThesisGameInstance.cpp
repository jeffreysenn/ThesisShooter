// Fill out your copyright notice in the Description page of Project Settings.

#include "C_ThesisGameInstance.h"
#include "FileHelper.h"
#include "Paths.h"

void UC_ThesisGameInstance::SaveDataToFile()
{

	UE_LOG(LogTemp, Warning, TEXT("@SaveDataToFile saving data to file "));
	FString DataContent = FString("Participant: " + PlayerIndex + LINE_TERMINATOR
		+ "Shots that hit target: " + FString::FromInt(ShotHits) + LINE_TERMINATOR
		+ "Total Shots fired: " + FString::FromInt(Shots) + LINE_TERMINATOR
		//+ "Amount of Targets hit: " +  FString::FromInt(TargetsHit) + LINE_TERMINATOR
		+ "Accuracy score: " + FString::FromInt(AccuracyScore) + LINE_TERMINATOR
		+ LINE_TERMINATOR
		+ "First section time: " + FString::SanitizeFloat(FirstSectionTime) + LINE_TERMINATOR
		+ "Second section time: " + FString::SanitizeFloat(SecondSectionTime) + LINE_TERMINATOR
		+ "Third section time: " + FString::SanitizeFloat(ThirdSectionTime) + LINE_TERMINATOR
		+ "Total time: " + FString::SanitizeFloat(FirstSectionTime + SecondSectionTime + ThirdSectionTime) + LINE_TERMINATOR
		+ "Hit Times On Shooting Section Targets: " + LINE_TERMINATOR);


	if (HitTimesFirstSectionTargets.Num())
	{
		for (int32 i = 0; i < HitTimesFirstSectionTargets.Num(); i++)
		{
			DataContent += FString("" + FString::SanitizeFloat(HitTimesFirstSectionTargets[i]) + LINE_TERMINATOR);
		}
	}

	DataContent += FString("Hit Times On Combined Section Targets:");
	DataContent += FString(+ LINE_TERMINATOR);

	if (HitTimesThirdSectionTargets.Num())
	{
		for (int32 i = 0; i < HitTimesThirdSectionTargets.Num(); i++)
		{
			DataContent += FString("" + FString::SanitizeFloat(HitTimesThirdSectionTargets[i]) + LINE_TERMINATOR);
		}
	}

	DataContent += FString(+LINE_TERMINATOR);
	FString FilePath = FPaths::ConvertRelativePathToFull(FPaths::GameSavedDir()) + TEXT("/DataLog_" + PlayerIndex + ".txt");
	FString FileContent = TEXT("" + DataContent);
	FFileHelper::SaveStringToFile(FileContent, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);

}
