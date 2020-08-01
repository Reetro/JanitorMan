// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Super_Rubble.generated.h"

UCLASS()
class JANITORMAN_API ASuper_Rubble : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASuper_Rubble();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UStaticMeshComponent* MyMesh;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UPhysicsHandleComponent* PhysicsHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};