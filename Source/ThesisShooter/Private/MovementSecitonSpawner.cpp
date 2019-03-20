// Fill out your copyright notice in the Description page of Project Settings.

#include "MovementSecitonSpawner.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "SectionTile.h"
#include "Components/ArrowComponent.h"


// Sets default values
AMovementSecitonSpawner::AMovementSecitonSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovementSecitonSpawner::BeginPlay()
{
	Super::BeginPlay();



	SpawnMovmeentSections(20);
}

// Called every frame
void AMovementSecitonSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMovementSecitonSpawner::SpawnMovmeentSections(int32 SectionsToSpawn)
{
	if (MovementSectionsThatCanSpawn.Num())
	{
		for (int32 i = 0; i < SectionsToSpawn; i++)
		{
			int32 rand = FMath::RandRange(0, MovementSectionsThatCanSpawn.Num()-1);
			ASectionTile* temp = NULL;

			if (MovementSectionsSpawned.Num()==0) 
			{
				temp = GetWorld()->SpawnActor<ASectionTile>(MovementSectionsThatCanSpawn[rand], this->GetActorLocation(), this->GetActorRotation());
				
				MovementSectionsSpawned.Add(temp);
				
			}
			else
			{
				if (MovementSectionsSpawned.Last())
				{
					FVector Pos = MovementSectionsSpawned.Last()->EndPosition->GetComponentLocation();


					//FVector Pos = MovementSectionsSpawned[MovementSectionsSpawned.Num() - 1]->EndPosition->GetComponentLocation();
					temp = GetWorld()->SpawnActor<ASectionTile>(MovementSectionsThatCanSpawn[rand], Pos, this->GetActorRotation());
					MovementSectionsSpawned.Add(temp);
				}
				else
				{
					return;
				}
			
				
			}
		

		}
		


	}
	else
	{
		return;
	}
}

