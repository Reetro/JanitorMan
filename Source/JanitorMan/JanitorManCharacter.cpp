// Copyright Epic Games, Inc. All Rights Reserved.

#include "JanitorManCharacter.h"
#include "JanitorManProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.h"
#include "ItemSpawner.h"
#include "Super_Item.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AJanitorManCharacter

AJanitorManCharacter::AJanitorManCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	ItemAttachMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Attach Mesh"));
	ItemAttachMesh->SetupAttachment(FirstPersonCameraComponent);
	ItemAttachMesh->SetHiddenInGame(true);
	ItemAttachMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("Physics Handel"));
	Grabber = CreateDefaultSubobject<UGrabber>(TEXT("Grabber"));
	ItemSpawner = CreateDefaultSubobject<UItemSpawner>(TEXT("Item Spawner"));
}

//////////////////////////////////////////////////////////////////////////
// Input

void AJanitorManCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AJanitorManCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AJanitorManCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AJanitorManCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AJanitorManCharacter::LookUpAtRate);
}

void AJanitorManCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AJanitorManCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AJanitorManCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AJanitorManCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AJanitorManCharacter::SetCurrentItem(ASuper_Item* Item)
{
	if (!ensure(Item != nullptr)) { return; }

	if (!CurrentItem)
	{
		CurrentItem = Item;
	}
	else
	{
		return;
	}

	AttachItem(Cast<AActor>(Item));
}

void AJanitorManCharacter::RemoveItem(ASuper_Item* Item, FTransform NewItemTransform, bool Reset)
{
	if (!ensure(Item != nullptr)) { return; }

	auto Actor = Cast<AActor>(Item);
	DetachItem(Actor, NewItemTransform, Reset);
}

void AJanitorManCharacter::AttachItem(AActor* Actor)
{
	if (!ensure(Actor != nullptr)) { return; }

	auto Item = Cast<ASuper_Item>(Actor);

	if (!ensure(Item != nullptr)) { return; }

	Item->OnItemAttached(this);
}

void AJanitorManCharacter::DetachItem(AActor* Actor, FTransform NewItemTransform, bool Reset)
{
	if (!ensure(Actor != nullptr)) { return; }

	Actor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	Actor->SetActorTransform(NewItemTransform);

	auto Item = Cast<ASuper_Item>(Actor);

	if (!ensure(Item != nullptr)) { return; }

	Item->OnItemRemoved(Reset);

	CurrentItem = nullptr;
}