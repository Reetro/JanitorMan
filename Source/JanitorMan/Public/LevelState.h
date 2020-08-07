// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RankDetails.h"
#include "GameFramework/Actor.h"
#include "RankDetails.h"
#include "LevelState.generated.h"

class ASuper_LevelPoint;

UCLASS()
class JANITORMAN_API ALevelState : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelState();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Level Events")
	void OnLevelDone();
	void OnLevelDone_Implementation();

	UFUNCTION(BlueprintCallable, Category = "Level Function")
	void StartTimer();

	UFUNCTION(BlueprintCallable, Category = "Level Function")
	void RefreshTimer();

	UFUNCTION(BlueprintImplementableEvent, Category = "Level Function")
	void OnTimerDone();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Level Events")
	void OnTimerTick();

	// Teleports player to the next level index
	UFUNCTION(BlueprintCallable, Category = "Level Function")
	void LoadNextLevel();

	// Called after player is teleport ed to new level
	void OnLevelLoaded();

	// How long the level lasts for
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Level Settings")
	float LevelTime = 60.0f;

	// Where to teleport the player when a level is completed
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Level Settings")
	TArray<ASuper_LevelPoint*> LevelPoints;

	// Trash need to get S rank
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Level Settings")
	FRankDetails SRank;
	// Trash need to get A rank
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Level Settings")
	FRankDetails ARank;
	// Trash need to get B rank
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Level Settings")
	FRankDetails BRank;
	// Trash need to get C rank
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Level Settings")
	FRankDetails CRank;
	// Trash need to get F rank
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Level Settings")
	FRankDetails FRank;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Level Settings")
	float TimeDivider;

	UPROPERTY(BlueprintReadOnly, Category = "Level Settings")
	float TimeRemaining;

	// Name of the level file
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Level Settings")
	FName LevelFileName;

	UPROPERTY(BlueprintReadWrite)
	FString CurrentRank;

	void AddToTrashCount();

	UPROPERTY(BlueprintReadOnly)
	bool OnLastLevel;
	UPROPERTY(BlueprintReadOnly)
	bool WonLevel;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Settings")
	FString MinRankToWinOnLevel1;

	// Reloads the current level the player is in
	UFUNCTION(BlueprintCallable, Category = "Level Function")
	void ReloadLevel();

	UFUNCTION(BlueprintCallable, Category = "Level Function")
	void SaveGame();

	UFUNCTION(BlueprintPure, Category = "Level Function")
	FName GetRankLevel();

	void LoadGame();

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 CurrentTrashCount = 0;

	float TimeLeft;
	float TimerDeltaTick;
	bool BeenRanked;
	bool OnLevelOne;

	int32 LevelIndex;

	FString GetRank();
	bool PlayerWonLevelCheck();

	FTimerHandle LevelTimerHandel;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};