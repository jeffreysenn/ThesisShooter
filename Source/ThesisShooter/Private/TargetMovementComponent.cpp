// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TargetMovementComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/TargetPoint.h"
#include "../Public/Target.h"

// Sets default values for this component's properties
UTargetMovementComponent::UTargetMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	TargetPoints.SetNum(1);
}


// Called when the game starts
void UTargetMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	SetTargetLocations();
	
}

void UTargetMovementComponent::SetTargetLocations()
{
	PreLocation = GetOwner()->GetActorLocation();
	NextTargetIndex = 0;
	TargetLocations.Add(GetOwner()->GetActorLocation());
	for (ATargetPoint* TargetPoint : TargetPoints)
	{
		if (!TargetPoint) { return; }
		 TargetLocations.Add(TargetPoint->GetActorLocation());
	}
}


// Called every frame
void UTargetMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!TargetPoints[0]) { return; }
	if (!Cast<ATarget>(GetOwner())->bIsShootable) 
	{
		PreLocation = GetOwner()->GetActorLocation();
		return; 
	}

	if (FVector::Dist(GetOwner()->GetActorLocation(), PreLocation) <= FVector::Dist(TargetLocations[NextTargetIndex], PreLocation))
	{
		FVector Direction = (TargetLocations[NextTargetIndex] - PreLocation).GetSafeNormal();
		GetOwner()->AddActorWorldOffset(Direction * SpeedPerSecond * DeltaTime);
	}
	else
	{
		GetOwner()->SetActorLocation(TargetLocations[NextTargetIndex]);
		MoveToNextTarget();
	}
}

void UTargetMovementComponent::MoveToNextTarget()
{
	PreLocation = GetOwner()->GetActorLocation();
	NextTargetIndex = (NextTargetIndex + 1) % TargetLocations.Num();
}

