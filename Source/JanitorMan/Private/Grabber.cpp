// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include <Runtime\Engine\Public\DrawDebugHelpers.h>


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// Get input component from owner and setup input
	FindInputComponent();

	/// Look for attached physics handler
	FindAttachedPhysicsComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PhysicsHandle) { return; }

	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}
}

void UGrabber::Grab()
{
	/// LINE TRACE and see if we reach any actors with physics body collision channel set
	auto PhysicsHitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = PhysicsHitResult.GetComponent();
	auto ActorHit = PhysicsHitResult.GetActor();

	auto PawnHitResult = GetFirstPawnInReach();
	auto PawnHit = PawnHitResult.GetActor();

	/// If we hit something then attach a physics handle
	if (PawnHit)
	{
		UE_LOG(LogTemp, Log, TEXT("Test"))
	}
	else if (PhysicsHandle)
	{
		if (ActorHit)
		{
			// attach physics handle
			PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), ComponentToGrab->GetOwner()->GetActorRotation());
		}
	}
}

void UGrabber::Released()
{
	if (!PhysicsHandle) { return; }
	PhysicsHandle->ReleaseComponent();
}

void UGrabber::FindAttachedPhysicsComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (!ensure(PhysicsHandle != nullptr)) { return; }
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FVector LineTraceStart = GetReachLineStart();
	FVector LineTraceEnd = GetReachLineEnd();

	/// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Line-trace (AKA ray-cast) out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, LineTraceStart, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameters);

	if (DebugPickup)
	{
		DrawDebugLine(GetWorld(), LineTraceStart, LineTraceEnd, FColor::Green, false, 5.0f, 0.0f, 10.0f);

		if (Hit.Actor != nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("Hit: %s"), *Hit.Actor->GetName());
		}
	}

	return Hit;
}

const FHitResult UGrabber::GetFirstPawnInReach()
{
	FVector LineTraceStart = GetReachLineStart();
	FVector LineTraceEnd = GetReachLineEnd();

	/// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Line-trace (AKA ray-cast) out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, LineTraceStart, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_Pawn), TraceParameters);

	if (DebugPickup)
	{
		DrawDebugLine(GetWorld(), LineTraceStart, LineTraceEnd, FColor::Green, false, 5.0f, 0.0f, 10.0f);

		if (Hit.Actor != nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("Hit: %s"), *Hit.Actor->GetName());
		}
	}

	return Hit;
}

void UGrabber::FindInputComponent()
{
	UInputComponent* InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (!ensure(InputComponent != nullptr)) { return; }

	InputComponent->BindAction("Interact", IE_Pressed, this, &UGrabber::GrabPressed);
	InputComponent->BindAction("Interact", IE_Released, this, &UGrabber::GrabReleesed);
}

FVector UGrabber::GetReachLineStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	return PlayerViewPointLocation;
}

FVector UGrabber::GetReachLineEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

void UGrabber::GrabPressed()
{
	Grab();
}

void UGrabber::GrabReleesed()
{
	Released();
}