// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetSpawner.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTargetSpawnerDelegate);

UCLASS()
class THESISSHOOTER_API ATargetSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetSpawner();

	TArray<AActor*> TargetObjs;

	UPROPERTY(EditAnywhere)
	TArray<class ATarget*> Targets;

	TArray<class ATarget*> StaticTargets;
	TArray<class ATarget*> MovingTargets;

	
	UPROPERTY(EditAnywhere)
	int32 StaticTargetNum = 10;

	UPROPERTY(EditAnywhere)
	int32 MovingTargetNum = 5;

	UPROPERTY(BlueprintAssignable)
	FTargetSpawnerDelegate OnAllTargitsHit;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int32 StaticTargetCount = 0;
	int32 MoveingTargetCount = 0;

	int32 PreStaticTargetIndex = -1;
	int32 PreMovingTargetIndex = -1;


	UFUNCTION()
	void ActivateRandomTarget(int32 UselessPoint);

	void ActivateStaticTarget();

	void ActivateMovingTarget();

	void DeactivateAllTargets();

	bool DoesTargetHaveTargetMovementComp(class ATarget* Target);

	int32 GetRandomInt(int32 From, int32 To, int32 Not = int32());

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SortAllTargets();


};
