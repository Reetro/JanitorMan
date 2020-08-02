// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelState.h"

// Sets default values
ALevelState::ALevelState()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TimerDeltaTick = 0.1f;
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
		OnTimerDone();
	}
	else
	{
		OnTimerTick();
	}
}

void ALevelState::OnTimerDone()
{
	OnLevelDone();
}

void ALevelState::AddToTrashCount()
{
	if (!BeenRanked)
	{
		CurrentTrashCount++;
	}
}

void ALevelState::OnLevelDone()
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandel);

	CurrentRank = GetRank();
}

FString ALevelState::GetRank()
{
	if (CurrentTrashCount >= SRankAmount)
	{
		return "S";
	}
	else if (CurrentTrashCount >= ARankAmount)
	{
		return "A";
	}
	else if (CurrentTrashCount >= BRankAmount)
	{
		return "B";
	}
	else if (CurrentTrashCount >= CRankAmount)
	{
		return "C";
	}
	else if (CurrentTrashCount >= FRankAmount || CurrentTrashCount <= FRankAmount)
	{
		return "F";
	}
	else
	{
		return "Unable to get rank";
	}
}