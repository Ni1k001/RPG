// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "RPGItemRarityEnum.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ItemRarityEnum : uint8
{
	ECommon				UMETA(DisplayName = "Common"),
	ERare				UMETA(DisplayName = "Rare"),
	EEpic				UMETA(DisplayName = "Epic"),
	ELegendary			UMETA(DisplayName = "Legendary"),
};