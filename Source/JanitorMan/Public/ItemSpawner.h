// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemSpawner.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JANITORMAN_API UItemSpawner : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemSpawner();

	UFUNCTION() void OnHitActor(AActor* Actor);

	virtual void BeginPlay() override;

private:
	class UGrabber* Graber;

	class AJanitorManCharacter* Player;
};
