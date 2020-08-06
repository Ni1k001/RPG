// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"

#include "RPG/structs/RPGBaseItemStruct.h"

#include "RPGItemDataStruct.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FItemDataStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 StackAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBaseItemStruct BaseItemData;

	FItemDataStruct()
	{
		StackAmount = 0;
	}

	FORCEINLINE bool operator==(const FItemDataStruct& Other) const
	{
		 return (BaseItemData == Other.BaseItemData);
	}

	FORCEINLINE bool operator!=(const FItemDataStruct& Other) const
	{
		return !(*this == Other);
	}
};
