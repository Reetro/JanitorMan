// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RankDetails.h"
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

	UFUNCTION(BlueprintImplementableEvent, Category = "Level Function")
	void OnTimerDone();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Level Events")
	void OnTimerTick();

	// How long the level lasts for
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Level Settings")
	float LevelTime = 60.0f;

	// Trash need to get S rank
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Level Settings")
	int32 SRankRequirement;
	// Trash need to get A rank
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Level Settings")
	int32 ARankRequirement;
	// Trash need to get B rank
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Level Settings")
	int32 BRankRequirement;
	// Trash need to get C rank
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Level Settings")
	int32 CRankRequirement;
	// Trash need to get F rank
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Level Settings")
	int32 FRankRequirement;

	UPROPERTY(BlueprintReadOnly, Category = "Level Settings")
	float TimeRemaining;

	UPROPERTY(BlueprintReadWrite)
	FString CurrentRank;

	void AddToTrashCount();

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 CurrentTrashCount = 0;

	float TimeLeft;
	float TimerDeltaTick;
	bool BeenRanked;

	FString GetRank();

	FTimerHandle LevelTimerHandel;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};