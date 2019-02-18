// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THESISSHOOTER_API UTargetMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTargetMovementComponent();

	UPROPERTY(EditAnywhere, Category = "Setup")
	TArray<class ATargetPoint*> TargetPoints;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float TimeBetween = 6;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float AcceptanceRange = 10;

protected:
	TArray<FVector> TargetLocations;
	int32 PreTargetIndex, NextTargetIndex;
	float TimeSinceStartedMove;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SetTargetLocations();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void MoveToNextTarget();
		
};
