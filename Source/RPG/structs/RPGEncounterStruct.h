// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "RPGEncounterStruct.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FIEncounterStruct
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<int32, FName> Enemies;

	FIEncounterStruct()
	{
		
	}
};
