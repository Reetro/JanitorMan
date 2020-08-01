// Fill out your copyright notice in the Description page of Project Settings.


#include "Super_Rubble.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values
ASuper_Rubble::ASuper_Rubble()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("Physics Handel"));

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MyMesh;
}

// Called when the game starts or when spawned
void ASuper_Rubble::BeginPlay()
{
	Super::BeginPlay();
	
}