// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "RPGTargetingTypeEnum.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class TargetingTypeEnum : uint8
{
	EOOnlySelf				UMETA(DisplayName = "OnlySelf"),
	ESingleAlly				UMETA(DisplayName = "SingleAlly"),
	ESingleEnemy			UMETA(DisplayName = "SingleEnemy"),
	EAllAllies				UMETA(DisplayName = "AllAllies"),
	EAllEnemies				UMETA(DisplayName = "AllEnemies"),
};