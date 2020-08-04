// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Super_TrashCan.generated.h"

UCLASS()
class JANITORMAN_API ASuper_TrashCan : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASuper_TrashCan();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UBoxComponent* BoxCollison;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	class ATrashCounter* TrashCounter;

	/* Gets all actors in the trash can */
	FORCEINLINE TArray<AActor*> GetActorsInTrash() { return ActorsInCan; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	class ALevelState* LevelState = nullptr;

	void GetLevelState();

	TArray<AActor*> ActorsInCan;

	bool DoesActorExistInCan(AActor* Actor);
};