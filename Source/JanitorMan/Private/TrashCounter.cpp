// Fill out your copyright notice in the Description page of Project Settings.


#include "TrashCounter.h"
#include "Components/BoxComponent.h"
#include "Super_TrashCan.h"
#include "../JanitorManCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "LevelState.h"

// Sets default values
ATrashCounter::ATrashCounter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BoxCollison = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	RootComponent = BoxCollison;
	BoxCollison->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void ATrashCounter::BeginPlay()
{
	Super::BeginPlay();

	GetLevelState();
}

void ATrashCounter::GetLevelState()
{
	TArray<AActor*> Actors;

	auto LevelStateActor = UGameplayStatics::GetActorOfClass(this, ALevelState::StaticClass());

	LevelState = Cast<ALevelState>(LevelStateActor);

	if (!ensure(LevelState != nullptr)) { return; }
}

void ATrashCounter::AreAllActorsInTrash()
{
	if (!ensure(TrashCan != nullptr)) { return; }

	TArray<AActor*> ActorsInLevel;

	BoxCollison->GetOverlappingActors(ActorsInLevel);

	int32 TrashCount = 0;

	for (AActor* Actor : ActorsInLevel)
	{
		if (Actor)
		{
			auto Player = Cast<AJanitorManCharacter>(Actor);
			
			if (!Player)
			{
				TrashCount++;
			}
		}
	}

	if (TrashCan->GetActorsInTrash().Num() >= TrashCount)
	{
		LevelState->OnLevelDone();
	}
}