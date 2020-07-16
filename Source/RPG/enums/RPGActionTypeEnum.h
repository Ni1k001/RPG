// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "RPGActionTypeEnum.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ActionTypeEnum : uint8
{
	EAttack				UMETA(DisplayName = "Attack"),
	EDefend				UMETA(DisplayName = "Defend"),
	EItems				UMETA(DisplayName = "Items"),
	EMagic				UMETA(DisplayName = "Magic"),
	EFlee				UMETA(DisplayName = "Flee"),
};