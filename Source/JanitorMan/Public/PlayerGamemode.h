// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerGamemode.generated.h"

/**
 * 
 */
UCLASS()
class JANITORMAN_API APlayerGamemode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void AddToPlayerCash(float Amount);

	void RemovePlayerCash(float Amount);

	void SetPlayerCash(float Cash);

	// Gets player current cash count
	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetCash() { return PlayerCash; }

private:
	float PlayerCash;
};
