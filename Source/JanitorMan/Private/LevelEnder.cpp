// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelEnder.h"
#include "PlayerSaveGame.h"
#include "LevelState.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelEnder::ALevelEnder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TimeRemaining = 0;
	Rank = "";
	TrashCount = 0;
	OnLastLevel = false;
}

void ALevelEnder::LoadGame()
{
	UPlayerSaveGame* SaveGameInstance = Cast<UPlayerSaveGame>(UGameplayStatics::CreateSaveGameObject(UPlayerSaveGame::StaticClass()));

	if (!ensure(SaveGameInstance != nullptr)) { return; }

	SaveGameInstance = Cast<UPlayerSaveGame>(UGameplayStatics::LoadGameFromSlot("TempSlot", 0));

	if (!ensure(SaveGameInstance != nullptr)) { return; }

	TimeRemaining = SaveGameInstance->TimeRemaining;
	Rank = SaveGameInstance->CurrentRank;
	TrashCount = SaveGameInstance->TrashCount;
	OnLastLevel = SaveGameInstance->OnLastLevel;
	TrashCount = SaveGameInstance->TrashCount;
}