// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpawner.h"
#include "Grabber.h"
#include "Super_Item.h"
#include "../JanitorManCharacter.h"

// Sets default values for this component's properties
UItemSpawner::UItemSpawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UItemSpawner::OnHitActor(AActor* Actor)
{
	if (Player->GetCurrentItem())
	{
		Player->GetCurrentItem()->OnItemUsed(Actor);
	}
}

void UItemSpawner::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AJanitorManCharacter>(GetOwner());

	if (!ensure(Player != nullptr)) { return; }
}