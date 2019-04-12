// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "C_ThesisGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class THESISSHOOTER_API UC_ThesisGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:

	

	virtual void SaveDataToFile();



	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PlayerIndex;

	UPROPERTY(VisibleAnywhere)
		int32 ShotHits=0;
	UPROPERTY(VisibleAnywhere)
		int32 Shots=0;

	int32 TargetsHit=0;
	UPROPERTY(VisibleAnywhere)
		int32 AccuracyScore=0;

	UPROPERTY(VisibleAnywhere)
		float FirstSectionTime=0;
	float SecondSectionTime=0;
	float ThirdSectionTime=0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 GameSection = 0;


	TArray<float> HitTimesFirstSectionTargets;

	TArray<float> HitTimesThirdSectionTargets;
	
};
