// Fill out your copyright notice in the Description page of Project Settings.

#include "ThesisTriggerVolume.h"
#include "C_ThesisGameInstance.h"
#include "Runtime/Engine/Classes/Engine/World.h"

// Sets default values
AThesisTriggerVolume::AThesisTriggerVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AThesisTriggerVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThesisTriggerVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AThesisTriggerVolume::SwitchGameSectionState(int32 StateToSwitchTo)
{
	if (Cast<UC_ThesisGameInstance>(GetWorld()->GetGameInstance()))
	{
		Cast<UC_ThesisGameInstance>(GetWorld()->GetGameInstance())->GameSection = StateToSwitchTo;
	}
	else {
		return;
	}
}

void AThesisTriggerVolume::SaveDataToFile()
{
	if (Cast<UC_ThesisGameInstance>(GetWorld()->GetGameInstance()))
	{
		Cast<UC_ThesisGameInstance>(GetWorld()->GetGameInstance())->SaveDataToFile();
	}
	else
	{
		return;
	}
}

