// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelState.h"
#include "Kismet/GameplayStatics.h"
#include "../JanitorManCharacter.h"
#include "Super_LevelPoint.h"

// Sets default values
ALevelState::ALevelState()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TimerDeltaTick = 0.1f;

	SRank.Requirement = 10;
	ARank.Requirement = 8;
	BRank.Requirement = 6;
	CRank.Requirement = 4;
	FRank.Requirement = 2;
}

void ALevelState::BeginPlay()
{
	Super::BeginPlay();

	CurrentTrashCount = 0;
	BeenRanked = false;
	LevelIndex = 0;
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

	OnLastLevel = LevelIndex >= LevelPoints.Num();

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);

	if (!ensure(PC != nullptr)) { return; }

	PC->bShowMouseCursor = true;
	PC->bEnableClickEvents = true;
	PC->bEnableMouseOverEvents = true;
}

FString ALevelState::GetRank()
{
	if (CurrentTrashCount >= SRank.Requirement)
	{
		return "S";
	}
	else if (CurrentTrashCount >= ARank.Requirement)
	{
		return "A";
	}
	else if (CurrentTrashCount >= BRank.Requirement)
	{
		return "B";
	}
	else if (CurrentTrashCount >= CRank.Requirement)
	{
		return "C";
	}
	else if (CurrentTrashCount >= FRank.Requirement || CurrentTrashCount <= FRank.Requirement)
	{
		return "F";
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to give player a rank"))
		return "Unable to get rank";
	}
}

void ALevelState::LoadNextLevel()
{
	AJanitorManCharacter* Player = Cast<AJanitorManCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (!ensure(Player != nullptr)) { return; }
	
	if (Player->GetCurrentItem())
	{
		Player->RemoveItem(Player->GetCurrentItem(), Player->GetActorTransform(), true);
	}

	if (!OnLastLevel)
	{
		FVector NextLevelPoint = LevelPoints[LevelIndex]->GetActorLocation();
		FRotator NextLevelRotation = LevelPoints[LevelIndex]->GetActorRotation();

		Player->TeleportTo(NextLevelPoint, NextLevelRotation, true, true);

		BeenRanked = false;

		LevelIndex = FMath::Clamp(LevelIndex + 1, 0, LevelPoints.Num());
	}

	OnLevelLoaded();
}

void ALevelState::OnLevelLoaded_Implementation()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);

	if (!ensure(PC != nullptr)) { return; }

	PC->bShowMouseCursor = false;
	PC->bEnableClickEvents = false;
	PC->bEnableMouseOverEvents = false;
}

void ALevelState::ReloadLevel()
{
	OnLevelLoaded();

	UGameplayStatics::OpenLevel(this, LevelFileName, false);
}