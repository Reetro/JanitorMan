// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrashCounter.generated.h"

UCLASS()
class JANITORMAN_API ATrashCounter : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxCollison;
	
public:	
	// Sets default values for this actor's properties
	ATrashCounter();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	class ASuper_TrashCan* TrashCan;

	void AreAllActorsInTrash();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class ALevelState* LevelState;
	void GetLevelState();
};
