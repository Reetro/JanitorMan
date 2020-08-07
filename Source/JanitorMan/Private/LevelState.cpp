// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelState.h"
#include "Kismet/GameplayStatics.h"
#include "../JanitorManCharacter.h"
#include "PlayerSaveGame.h"
#include "Super_LevelPoint.h"

// Sets default values
ALevelState::ALevelState()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TimerDeltaTick = 0.1f;
	MinRankToWinOnLevel1 = "C";
	TimeDivider = 2;

	SRank.Requirement = 10;
	ARank.Requirement = 8;
	BRank.Requirement = 6;
	CRank.Requirement = 4;
	FRank.Requirement = 2;
}

void ALevelState::BeginPlay()
{
	Super::BeginPlay();

	if (UGameplayStatics::DoesSaveGameExist("TempSlot", 0))
	{
		CurrentTrashCount = 0;
		BeenRanked = false;
		OnLevelOne = false;

		LoadGame();
	}
	else
	{
		CurrentTrashCount = 0;
		BeenRanked = false;
		LevelIndex = 0;
		OnLevelOne = true;
	}
}

void ALevelState::StartTimer()
{
	if (!OnLevelOne)
	{
		TimeRemaining = LevelTime / TimeDivider;

		GetWorldTimerManager().SetTimer(LevelTimerHandel, this, &ALevelState::RefreshTimer, TimerDeltaTick, true);
	}
	else
	{
		TimeRemaining = LevelTime;

		GetWorldTimerManager().SetTimer(LevelTimerHandel, this, &ALevelState::RefreshTimer, TimerDeltaTick, true);
	}
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

	OnLastLevel = LevelIndex >= LevelPoints.Num();

	CurrentRank = GetRank();

	WonLevel = PlayerWonLevelCheck();

	BeenRanked = true;

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

bool ALevelState::PlayerWonLevelCheck()
{
	if (OnLevelOne)
	{
		if (CurrentRank.Contains(MinRankToWinOnLevel1))
		{
			return true;
		}
		if (CurrentRank.Contains("S"))
		{
			return true;
		}
		else if (CurrentRank.Contains("A"))
		{
			return true;
		}
		else if (CurrentRank.Contains("B"))
		{
			return true;
		}
		else if (CurrentRank.Contains("C"))
		{
			return true;
		}
		else if (CurrentRank.Contains("F"))
		{
			return false;
		}
		else
		{
			return false;
		}
	}
	else if (OnLastLevel)
	{
		if (CurrentRank.Contains(MinRankToWinOnLevel1))
		{
			return true;
		}
		if (CurrentRank.Contains("S"))
		{
			return true;
		}
		else if (CurrentRank.Contains("A"))
		{
			return true;
		}
		else if (CurrentRank.Contains("B"))
		{
			return true;
		}
		else if (CurrentRank.Contains("C"))
		{
			return true;
		}
		else if (CurrentRank.Contains("F"))
		{
			return false;
		}
		else
		{
			return false;
		}
	}
	else
	{
		auto CurrentLevelPoint = LevelPoints[LevelIndex];

		if (!ensure(CurrentLevelPoint != nullptr)) { return false; }

		if (CurrentRank.Contains(CurrentLevelPoint->MinRankToWin))
		{
			return true;
		}
		if (CurrentRank.Contains("S"))
		{
			return true;
		}
		else if (CurrentRank.Contains("A"))
		{
			return true;
		}
		else if (CurrentRank.Contains("B"))
		{
			return true;
		}
		else if (CurrentRank.Contains("C"))
		{
			return true;
		}
		else if (CurrentRank.Contains("F"))
		{
			return false;
		}
		else
		{
			return false;
		}
	}
}

FName ALevelState::GetRankLevel()
{
	if (CurrentRank.Contains("S"))
	{
		return SRank.RankLevel;
	}
	else if (CurrentRank.Contains("A"))
	{
		return ARank.RankLevel;
	}
	else if (CurrentRank.Contains("B"))
	{
		return BRank.RankLevel;
	}
	else if (CurrentRank.Contains("C"))
	{
		return CRank.RankLevel;
	}
	else if (CurrentRank.Contains("F"))
	{
		return FRank.RankLevel;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get rank level"))
		return "Unable to get rank level";
	}
}

void ALevelState::SaveGame()
{
	UPlayerSaveGame* SaveGameInstance = Cast<UPlayerSaveGame>(UGameplayStatics::CreateSaveGameObject(UPlayerSaveGame::StaticClass()));

	if (!ensure(SaveGameInstance != nullptr)) { return; }
	
	SaveGameInstance->TimeRemaining = TimeRemaining;
	SaveGameInstance->TrashCount = CurrentTrashCount;
	SaveGameInstance->LevelIndex = LevelIndex;
	SaveGameInstance->CurrentRank = CurrentRank;
	SaveGameInstance->OnLastLevel = OnLastLevel;
	SaveGameInstance->WonLevel = WonLevel;

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, "TempSlot", 0);
}

void ALevelState::LoadGame()
{
	UPlayerSaveGame* SaveGameInstance = Cast<UPlayerSaveGame>(UGameplayStatics::CreateSaveGameObject(UPlayerSaveGame::StaticClass()));

	if (!ensure(SaveGameInstance != nullptr)) { return; }

	SaveGameInstance = Cast<UPlayerSaveGame>(UGameplayStatics::LoadGameFromSlot("TempSlot", 0));

	if (!ensure(SaveGameInstance != nullptr)) { return; }

	LevelIndex = SaveGameInstance->LevelIndex;

	LoadNextLevel();
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

void ALevelState::OnLevelLoaded()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);

	if (!ensure(PC != nullptr)) { return; }

	PC->bShowMouseCursor = false;
	PC->bEnableClickEvents = false;
	PC->bEnableMouseOverEvents = false;

	OnLevelOne = false;
}

void ALevelState::ReloadLevel()
{
	OnLevelLoaded();

	UGameplayStatics::DeleteGameInSlot("TempSlot", 0);

	UGameplayStatics::OpenLevel(this, LevelFileName, false);
}