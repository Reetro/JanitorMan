// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelState.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelState::ALevelState()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TimerDeltaTick = 0.1f;

	SRankRequirement = 10;
	ARankRequirement = 8;
	BRankRequirement = 6;
	CRankRequirement = 4;
	FRankRequirement = 2;
}

void ALevelState::BeginPlay()
{
	Super::BeginPlay();

	CurrentTrashCount = 0;
	BeenRanked = false;
}

void ALevelState::StartTimer()
{
	TimeRemaining = LevelTime;

	GetWorldTimerManager().SetTimer(LevelTimerHandel, this, &ALevelState::RefreshTimer, TimerDeltaTick, true);
}

void ALevelState::RefreshTimer()
{
	TimeRemaining -= TimerDeltaTick;

	if (TimeRemaining <= 0)
	{
		TimeRemaining = 0.0f;

		OnTimerDone();

		OnLevelDone();
	}
	else
	{
		OnTimerTick();
	}
}

void ALevelState::AddToTrashCount()
{
	if (!BeenRanked)
	{
		CurrentTrashCount++;
	}
}

void ALevelState::OnLevelDone_Implementation()
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandel);

	CurrentRank = GetRank();

	BeenRanked = true;
}

FString ALevelState::GetRank()
{
	if (CurrentTrashCount >= SRankRequirement)
	{
		return "S";
	}
	else if (CurrentTrashCount >= ARankRequirement)
	{
		return "A";
	}
	else if (CurrentTrashCount >= BRankRequirement)
	{
		return "B";
	}
	else if (CurrentTrashCount >= CRankRequirement)
	{
		return "C";
	}
	else if (CurrentTrashCount >= FRankRequirement || CurrentTrashCount <= FRankRequirement)
	{
		return "F";
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to give player a rank"))
		return "Unable to get rank";
	}
}