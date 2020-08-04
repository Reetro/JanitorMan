// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpawner.h"
#include "Grabber.h"
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
		FTransform NewTransform = FTransform(FRotator(0), Actor->GetActorLocation(), FVector(0.7));

		Player->RemoveItem(Player->GetCurrentItem(), NewTransform);

		Actor->Destroy();
	}
}

void UItemSpawner::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AJanitorManCharacter>(GetOwner());

	if (!ensure(Player != nullptr)) { return; }
}