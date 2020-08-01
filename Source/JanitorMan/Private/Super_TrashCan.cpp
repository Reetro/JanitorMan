// Fill out your copyright notice in the Description page of Project Settings.


#include "Super_TrashCan.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LevelState.h"

// Sets default values
ASuper_TrashCan::ASuper_TrashCan()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	BoxCollison = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollison->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void ASuper_TrashCan::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCollison->OnComponentBeginOverlap.AddDynamic(this, &ASuper_TrashCan::OnOverlapBegin);

	GetLevelState();
}

void ASuper_TrashCan::GetLevelState()
{
	TArray<AActor*> LevelStates;

	UGameplayStatics::GetAllActorsOfClass(this, ALevelState::StaticClass(), LevelStates);

	for (AActor* actor : LevelStates)
	{
		auto state = Cast<ALevelState>(actor);

		if (state)
		{
			LevelState = state;
		}
	}
}

void ASuper_TrashCan::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!ensure(LevelState != nullptr)) { return; }

	if (!LevelState->WonLevel)
	{
		LevelState->AddToTrashCount();
	}
}