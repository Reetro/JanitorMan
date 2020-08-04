// Fill out your copyright notice in the Description page of Project Settings.


#include "Super_Item.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "../JanitorManCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASuper_Item::ASuper_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	RootComponent = ItemMesh;

	BoxCollison = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollison->SetupAttachment(RootComponent);
}

void ASuper_Item::BeginPlay()
{
	Super::BeginPlay();

	BoxCollison->OnComponentBeginOverlap.AddDynamic(this, &ASuper_Item::OnOverlapBegin);

	CanBeUsed = true;
}

void ASuper_Item::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Player = Cast<AJanitorManCharacter>(OtherActor);
	
	if (Player)
	{
		Player->SetCurrentItem(this);
	}
}