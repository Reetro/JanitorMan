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
	UE_LOG(LogTemp, Log, TEXT("Timer Done"))

	LostLevel = true;
	WonLevel = false;

	OnLevelDone();
}

void ALevelState::AddToTrashCount()
{
	CurrentTrashCount++;

	if (CurrentTrashCount >= MaxTrash)
	{
		WonLevel = true;
		LostLevel = false;

		OnLevelDone();
	}
}

void ALevelState::OnLevelDone()
{
	UpdateRank("S");

	if (WonLevel)
	{
		// TODO Create a win state
		UE_LOG(LogTemp, Log, TEXT("Level Won"))

		GetWorldTimerManager().ClearTimer(LevelTimerHandel);
	}
	else if (LostLevel)
	{
		// TODO Create a game over state
		UE_LOG(LogTemp, Log, TEXT("Level Lost"))

		GetWorldTimerManager().ClearTimer(LevelTimerHandel);
	}
}