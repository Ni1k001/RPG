// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "RPGItemTypeEnum.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ItemTypeEnum : uint8
{
	EMeleeWeapon				UMETA(DisplayName = "MeleeWeapon"),
	ERangedWeapon				UMETA(DisplayName = "RangedWeapon"),
	EArmor						UMETA(DisplayName = "Armor"),
	EAccessory					UMETA(DisplayName = "Accessory"),
	EConsumable					UMETA(DisplayName = "Consumable"),
	EKeyItem					UMETA(DisplayName = "KeyItem"),
	EMiscellaneous				UMETA(DisplayName = "Miscellaneous"),
};

