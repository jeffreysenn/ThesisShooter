// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TargetSpawner.h"
#include "../Public/Target.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATargetSpawner::ATargetSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATargetSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	FindAllTargets();
	DeactivateAllTargets();
	ActivateRandomTarget(0);
}



void ATargetSpawner::ActivateRandomTarget(int32 UselessPoint)
{
	UE_LOG(LogTemp, Warning, TEXT("Try Activate!"));
	int32 NextIndex = FMath::RandRange(0, Targets.Num()-1);
	ATarget* TargetToActive = Targets[NextIndex];
	if (!TargetToActive) { return; }
	TargetToActive->OnTargetHitDelegate.AddUniqueDynamic(this, &ATargetSpawner::ActivateRandomTarget);
	TargetToActive->ActivateTarget();
}

void ATargetSpawner::DeactivateAllTargets()
{
	for (ATarget* Target : Targets)
	{
		Target->DeactivateTarget();
	}
}

// Called every frame
void ATargetSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATargetSpawner::FindAllTargets()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATarget::StaticClass(), TargetObjs);
	for (AActor* TargetObj : TargetObjs)
	{
		Targets.Add(Cast<ATarget>(TargetObj));
	}
}

