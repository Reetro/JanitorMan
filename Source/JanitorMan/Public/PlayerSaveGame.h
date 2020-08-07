// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PlayerSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class JANITORMAN_API UPlayerSaveGame : public USaveGame
{
	GENERATED_BODY()
	

public:
	UPlayerSaveGame();

	UPROPERTY(EditAnywhere)
	FString CurrentRank;
	UPROPERTY(EditAnywhere)
	float TimeRemaining;
	UPROPERTY(EditAnywhere)
	int32 LevelIndex;
	UPROPERTY(EditAnywhere)
	int32 TrashCount;
	UPROPERTY(EditAnywhere)
	bool OnLastLevel;
};
