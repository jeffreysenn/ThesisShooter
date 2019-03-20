// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SectionTile.generated.h"

UCLASS()
class THESISSHOOTER_API ASectionTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASectionTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, Instanced)//Category = "Arrow")
	class USceneComponent * StartPosition;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SpawnPoint")
	class USceneComponent * EndPosition;

	UFUNCTION(BlueprintCallable)
		void SetEndPosition(class USceneComponent * PointToSet);

};
