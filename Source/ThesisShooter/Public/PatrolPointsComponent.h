// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolPointsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THESISSHOOTER_API UPatrolPointsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPatrolPointsComponent();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite ,Category = "Patrol")
	TArray<class ATargetPoint*> PatrolPoints;
		
};
