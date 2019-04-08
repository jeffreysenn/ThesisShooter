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
	float SpeedPerSecond = 50;

protected:
	TArray<FVector> TargetLocations;
	FVector PreLocation;
	int32 NextTargetIndex;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SetTargetLocations();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void MoveToNextTarget();
		
};
