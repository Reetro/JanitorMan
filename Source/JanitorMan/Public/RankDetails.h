// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RankDetails.generated.h"

USTRUCT(BlueprintType)
struct FRankDetails
{
	GENERATED_BODY()

public:
	// Level to send player to
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FName RankLevel;
	// Amount of trash needed to get this rank
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int32 Requirement;
};