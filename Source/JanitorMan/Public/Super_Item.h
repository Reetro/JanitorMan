// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Super_Item.generated.h"

UCLASS()
class JANITORMAN_API ASuper_Item : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ItemMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxCollison;

public:	
	// Sets default values for this actor's properties
	ASuper_Item();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	FVector SizeInHand;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	FName SocketName;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item Events")
	void OnItemUsed(AActor* HitActor);
	void OnItemUsed_Implementation(AActor* HitActor);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Item Events")
	void OnItemPickup();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item Events")
	void OnItemRemoved(bool Reset);
	void OnItemRemoved_Implementation(bool Reset);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item Events")
	void OnItemAttached(class AJanitorManCharacter* PlayerRef);
	void OnItemAttached_Implementation(class AJanitorManCharacter* PlayerRef);

	UPROPERTY(BlueprintReadOnly)
	class AJanitorManCharacter* Player;
	UPROPERTY(BlueprintReadWrite)
	bool CanBeUsed;

	FORCEINLINE UBoxComponent* GetCollisionBox() { return BoxCollison; }
	FORCEINLINE UStaticMeshComponent* GetMesh() { return ItemMesh; }

	void UseDelay();

private:
	ASuper_Item* ItemToDelay;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
