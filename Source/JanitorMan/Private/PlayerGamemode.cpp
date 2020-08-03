// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGamemode.h"

void APlayerGamemode::AddToPlayerCash(float Amount)
{
	PlayerCash += Amount;
}

void APlayerGamemode::RemovePlayerCash(float Amount)
{
	PlayerCash -= Amount;
}

void APlayerGamemode::SetPlayerCash(float Cash)
{
	PlayerCash = Cash;
}