// Fill out your copyright notice in the Description page of Project Settings.

#include "SectionTile.h"
#include "Components/ArrowComponent.h"


// Sets default values
ASectionTile::ASectionTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("IndividualRootComponent"));
	
	
	//StartPosition = CreateDefaultSubobject<USceneComponent>(TEXT("StartPosition"));
	//EndPosition = CreateDefaultSubobject<USceneComponent>(TEXT("EndPosition"));
	
}

// Called when the game starts or when spawned
void ASectionTile::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ASectionTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASectionTile::SetEndPosition(USceneComponent* PointToSet)
{
	EndPosition = PointToSet;

}

