// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Target.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargetDelegate, int, score);

UCLASS()
class THESISSHOOTER_API ATarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATarget();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float TargetRadius = 50;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MiddleRingRadius = 40;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float InnerCircleRadius = 20;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int OuterRingScore = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int MiddleRingScore = 2;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int InnerCircleScore = 4;

	FTargetDelegate OnTargetHitDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	USceneComponent* Centre;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;




	UFUNCTION(BlueprintCallable)
	void FindCentreComponent(USceneComponent* CentreComponent);

	void OnTargetHit(FVector HitLocation);
};
