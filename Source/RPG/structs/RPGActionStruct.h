// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"

#include "RPG/enums/RPGActionTypeEnum.h"

#include "RPGActionStruct.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FActionStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ActionTypeEnum ActionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "100000", UIMin = "0", UIMax = "100000"))
		float BaseCostHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "100000", UIMin = "0", UIMax = "100000"))
		float BaseCostMP;

	FActionStruct()
	{
		Name = "";
		DisplayName = FText::FromString("");

		ActionType = ActionTypeEnum::EAttack;
		DisplayName = FText::FromString("");

		BaseCostMP = 0;
		BaseCostHP = 0;
	}
};