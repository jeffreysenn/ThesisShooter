// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovementSecitonSpawner.generated.h"

UCLASS()
class THESISSHOOTER_API AMovementSecitonSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovementSecitonSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TArray< TSubclassOf<class ASectionTile>> MovementSectionsThatCanSpawn;

	TArray<ASectionTile*> MovementSectionsSpawned;

	virtual void SpawnMovmeentSections(int32 SectionsToSpawn);

};
