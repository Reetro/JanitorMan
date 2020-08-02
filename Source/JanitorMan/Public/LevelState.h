// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelState.generated.h"

UCLASS()
class JANITORMAN_API ALevelState : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelState();

	UFUNCTION(BlueprintCallable, Category = "Level Function")
	void OnLevelDone();

	UFUNCTION(BlueprintCallable, Category = "Level Function")
	void StartTimer();

	UFUNCTION(BlueprintCallable, Category = "Level Function")
	void RefreshTimer();

	UFUNCTION(BlueprintCallable, Category = "Level Function")
	void OnTimerDone();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Level Events")
	void OnTimerTick();

	// How long the level lasts for
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Level Settings")
	float LevelTime = 60.0f;

	// Trash need to win
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Level Settings")
	int32 MaxTrash = 10;

	UPROPERTY(BlueprintReadOnly, Category = "Level Settings")
	float TimeRemaining;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Level Events")
	void UpdateRank(const FString& LevelRank);

	bool WonLevel = true;
	bool LostLevel = false;

	FString LevelScore;

	void AddToTrashCount();

private:
	int32 CurrentTrashCount = 0;

	float TimeLeft;
	float TimerDeltaTick;

	FTimerHandle LevelTimerHandel;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};