// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "RPGPartySlotStruct.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FPartySlotStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Name;

	FPartySlotStruct()
	{
		Name = "";
	}
};