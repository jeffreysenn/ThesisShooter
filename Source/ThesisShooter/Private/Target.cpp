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

void ATarget::OnTargetHit(FVector HitLocation)
{
	UE_LOG(LogTemp, Warning, TEXT("Recieve Hit!"));
	if (!Centre) { return; }
	float DistanceFromCentre = (HitLocation - Centre->GetComponentLocation()).Size();
	if (DistanceFromCentre > TargetRadius) { return; }
	else if (DistanceFromCentre > MiddleRingRadius)
	{
		OnTargetHitDelegate.Broadcast(OuterRingScore);
	}
	else if (DistanceFromCentre > InnerCircleRadius)
	{
		OnTargetHitDelegate.Broadcast(MiddleRingScore);
	}
	else
	{
		OnTargetHitDelegate.Broadcast(InnerCircleScore);
	}

}

void ATarget::FindCentreComponent(USceneComponent* CentreComponent)
{
	Centre = CentreComponent;
}

