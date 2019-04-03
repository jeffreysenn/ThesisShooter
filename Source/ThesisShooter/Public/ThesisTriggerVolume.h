// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThesisTriggerVolume.generated.h"

UCLASS()
class THESISSHOOTER_API AThesisTriggerVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThesisTriggerVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable)
	void SwitchGameSectionState(int32 StateToSwitchTo);

	UFUNCTION(BlueprintCallable)
	virtual void SaveDataToFile();

};
