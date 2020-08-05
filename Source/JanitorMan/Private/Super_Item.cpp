// Fill out your copyright notice in the Description page of Project Settings.


#include "Super_Item.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "../JanitorManCharacter.h"
#include "Grabber.h"
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

	SizeInHand = FVector(1);
}

void ASuper_Item::BeginPlay()
{
	Super::BeginPlay();

	BoxCollison->OnComponentBeginOverlap.AddDynamic(this, &ASuper_Item::OnOverlapBegin);

	Player = Cast<AJanitorManCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (ensure(Player != nullptr)) { return; }
}

void ASuper_Item::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (CanBeUsed && !Player->GetGrabber()->HoldingItem)
	{
		auto PlayerCharacter = Cast<AJanitorManCharacter>(OtherActor);

		if (PlayerCharacter)
		{
			CanBeUsed = false;
			PlayerCharacter->SetCurrentItem(this);
			OnItemPickup();
		}
	}
}

void ASuper_Item::OnItemUsed_Implementation(AActor* HitActor)
{
	if (!ensure(HitActor != nullptr)) { return; }

	FTransform NewTransform = FTransform(FRotator(0), HitActor->GetActorLocation(), FVector(0.7));

	Player->RemoveItem(Player->GetCurrentItem(), NewTransform, false);

	HitActor->Destroy();
}

void ASuper_Item::OnItemRemoved_Implementation(bool Reset)
{
	if (!Reset)
	{
		GetMesh()->SetCollisionObjectType(ECC_PhysicsBody);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		GetMesh()->SetSimulatePhysics(true);
	}
	else
	{
		CanBeUsed = true;

		GetMesh()->SetSimulatePhysics(true);
	}
}
