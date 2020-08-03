// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelState.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerGamemode.h"

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
	BRank.RankAmount = 6;

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

void ALevelState::OnLevelDone()
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandel);

	CurrentRank = GetRank();

	BeenRanked = true;

	AddPlayerCash();
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
		UE_LOG(LogTemp, Error, TEXT("Failed to give player a rank"))
		return "Unable to get rank";
	}
}

void ALevelState::AddPlayerCash()
{
	auto Gamemode = Cast<APlayerGamemode>(UGameplayStatics::GetGameMode(this));

	if (!ensure(Gamemode != nullptr)) { return; }

	if (CurrentRank.Contains("S"))
	{
		Gamemode->AddToPlayerCash(SRank.MoneyToGive);
	}
	else if (CurrentRank.Contains("A"))
	{
		Gamemode->AddToPlayerCash(ARank.MoneyToGive);
	}
	else if (CurrentRank.Contains("C"))
	{
		Gamemode->AddToPlayerCash(CRank.MoneyToGive);
	}
	else if (CurrentRank.Contains("F"))
	{
		Gamemode->AddToPlayerCash(FRank.MoneyToGive);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to give player cash. Player has no rank"))
	}
}