// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSaveGame.h"
#include "Kismet/GameplayStatics.h"

UPlayerSaveGame::UPlayerSaveGame()
{
	CurrentRank = "";
	TimeRemaining = 0;
	LevelIndex = 0;
	OnLastLevel = false;
	TrashCount = 0;
	WonLevel = false;
}