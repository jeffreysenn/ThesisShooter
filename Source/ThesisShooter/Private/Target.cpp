// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Target.h"

// Sets default values
ATarget::ATarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int ATarget::OnTargetHit(FVector HitLocation)
{
	UE_LOG(LogTemp, Warning, TEXT("Recieve Hit!"));
	if (!Centre) { return 0; }
	float DistanceFromCentre = (HitLocation - Centre->GetComponentLocation()).Size();
	if (DistanceFromCentre > TargetRadius) 
	{ 
		return 0; 
	}

	OnTargetDamaged();

	if (DistanceFromCentre > MiddleRingRadius && DistanceFromCentre <= TargetRadius)
	{
		OnTargetHitDelegate.Broadcast(OuterRingScore);
		UE_LOG(LogTemp, Warning, TEXT("HitOuterRing"));
		return OuterRingScore;

	}
	else if (DistanceFromCentre > InnerCircleRadius)
	{
		OnTargetHitDelegate.Broadcast(MiddleRingScore);
		UE_LOG(LogTemp, Warning, TEXT("HitMiddleRing"));
		return MiddleRingScore;
	}
	else
	{
		OnTargetHitDelegate.Broadcast(InnerCircleScore);
		UE_LOG(LogTemp, Warning, TEXT("HitBullsEye"));
		return InnerCircleScore;
	}


	return 0;

}

void ATarget::FindCentreComponent(USceneComponent* CentreComponent)
{
	Centre = CentreComponent;
}

