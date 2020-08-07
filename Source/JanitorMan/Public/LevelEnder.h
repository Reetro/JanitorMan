// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelEnder.generated.h"

UCLASS()
class JANITORMAN_API ALevelEnder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelEnder();

	UPROPERTY(BlueprintReadOnly)
	float TimeRemaining;

	UPROPERTY(BlueprintReadOnly)
	FString Rank;

	UPROPERTY(BlueprintReadOnly)
	int32 TrashCount;

	UPROPERTY(BlueprintReadOnly)
	bool OnLastLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	FName MainGameLevel;

	UFUNCTION(BlueprintCallable, Category = "Level Function")
	void LoadGame();
};