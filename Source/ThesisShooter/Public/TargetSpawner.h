// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetSpawner.generated.h"

UCLASS()
class THESISSHOOTER_API ATargetSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void ActivateRandomTarget(int32 UselessPoint);

	void DeactivateAllTargets();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FindAllTargets();

	TArray<AActor*> TargetObjs;

	UPROPERTY(EditAnywhere)
	TArray<class ATarget*> Targets;


};
