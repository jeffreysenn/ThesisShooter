// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TargetSpawner.h"
#include "../Public/Target.h"
#include "../Public/TargetMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATargetSpawner::ATargetSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATargetSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	SortAllTargets();
	DeactivateAllTargets();
	ActivateRandomTarget(0);
}



void ATargetSpawner::ActivateRandomTarget(int32 UselessPoint)
{
	UE_LOG(LogTemp, Warning, TEXT("Try Activate!"));
	if (StaticTargetCount < StaticTargetNum)
	{
		ActivateStaticTarget();
		StaticTargetCount++;
	}
	else if (MoveingTargetCount < MovingTargetNum)
	{
		ActivateMovingTarget();
		MoveingTargetCount++;
	}
}

void ATargetSpawner::ActivateStaticTarget()
{
	int32 NextIndex = GetRandomInt(0, StaticTargets.Num() - 1, PreStaticTargetIndex);
	PreStaticTargetIndex = NextIndex;

	ATarget* TargetToActive = StaticTargets[NextIndex];
	if (!TargetToActive) { return; }
	TargetToActive->OnTargetHitDelegate.AddUniqueDynamic(this, &ATargetSpawner::ActivateRandomTarget);
	TargetToActive->ActivateTarget();
}

void ATargetSpawner::ActivateMovingTarget()
{
	int32 NextIndex = GetRandomInt(0, MovingTargets.Num() - 1, PreMovingTargetIndex);
	PreMovingTargetIndex = NextIndex;

	ATarget* TargetToActive = MovingTargets[NextIndex];
	if (!TargetToActive) { return; }
	UTargetMovementComponent* TargetMovementComp = Cast<UTargetMovementComponent>(TargetToActive->GetComponentByClass(UTargetMovementComponent::StaticClass()));
	TargetToActive->OnTargetHitDelegate.AddUniqueDynamic(this, &ATargetSpawner::ActivateRandomTarget);
	TargetToActive->ActivateTarget();
	TargetMovementComp->MoveToNextTarget();


}

void ATargetSpawner::DeactivateAllTargets()
{
	for (ATarget* Target : Targets)
	{
		Target->DeactivateTarget();
	}
}

bool ATargetSpawner::DoesTargetHaveTargetMovementComp(ATarget * Target)
{
	if (!Target->GetComponentByClass(UTargetMovementComponent::StaticClass()))
	{
		return false;
	}
	return true;
}

int32 ATargetSpawner::GetRandomInt(int32 From, int32 To, int32 Not)
{
	if (From - To == 0) { return From; }
	int32 RandomInt = FMath::RandRange(From, To);
	if (RandomInt == Not)
	{
		RandomInt = GetRandomInt(From, To, Not);
	}
	return RandomInt;
}

// Called every frame
void ATargetSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATargetSpawner::SortAllTargets()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATarget::StaticClass(), TargetObjs);
	for (AActor* TargetObj : TargetObjs)
	{
		ATarget* Target = Cast<ATarget>(TargetObj);
		if (!Target) { continue; }
		Targets.Add(Target);
		if (DoesTargetHaveTargetMovementComp(Target))
		{
			MovingTargets.Add(Target);
		}
		else
		{
			StaticTargets.Add(Target);
		}
	}
}

