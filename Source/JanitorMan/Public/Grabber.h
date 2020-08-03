// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JANITORMAN_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/// Raycast and grab item in reach
	void Grab();
	/// Called when grab key is released
	void Released();

	/// The distance a player can reach in cm
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")
	float Reach = 100.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")
	bool DebugPickup = false;

private:

	class UPhysicsHandleComponent* PhysicsHandle = nullptr;

	void FindAttachedPhysicsComponent();

	void FindInputComponent();

	const FHitResult GetFirstPhysicsBodyInReach();

	FVector GetReachLineStart();

	FVector GetReachLineEnd();

	void GrabPressed();
	void GrabReleesed();
};