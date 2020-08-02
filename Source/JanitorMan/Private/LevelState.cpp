// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelState.h"

// Sets default values
ALevelState::ALevelState()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TimerDeltaTick = 0.1f;

	SRank.MoneyToGive = 100;
	SRank.RankAmount = 10;

	ARank.MoneyToGive = 90;
	ARank.RankAmount = 8;

	BRank.MoneyToGive = 80;
	CRank.RankAmount = 6;

	CRank.MoneyToGive = 70;
	CRank.RankAmount = 4;

	FRank.MoneyToGive = 60;
	FRank.RankAmount = 2;
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

	BeenRanked = true;
}

FString ALevelState::GetRank()
{
	if (CurrentTrashCount >= SRank.RankAmount)
	{
		return "S";
	}
	else if (CurrentTrashCount >= ARank.RankAmount)
	{
		return "A";
	}
	else if (CurrentTrashCount >= BRank.RankAmount)
	{
		return "B";
	}
	else if (CurrentTrashCount >= CRank.RankAmount)
	{
		return "C";
	}
	else if (CurrentTrashCount >= FRank.RankAmount || CurrentTrashCount <= FRank.RankAmount)
	{
		return "F";
	}
	else
	{
		return "Unable to get rank";
	}
}