// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RankDetails.generated.h"

USTRUCT(BlueprintType)
struct FRankDetails
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int32 MoneyToGive;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int32 RankAmount;
};