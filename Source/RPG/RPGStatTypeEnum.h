// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "RPGStatTypeEnum.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class StatsEnum : uint8
{
	EHP					UMETA(DisplayName = "HP"),
	EMP					UMETA(DisplayName = "MP"),
	EStrength			UMETA(DisplayName = "Strength"),
	EDexterity			UMETA(DisplayName = "Dexterity"),
	EVitality 			UMETA(DisplayName = "Vitality"),
	EMagic				UMETA(DisplayName = "Magic"),
	ESpirit				UMETA(DisplayName = "Spirit"),
	ELuck	 			UMETA(DisplayName = "Luck"),
	EInitiative			UMETA(DisplayName = "Initiative"),
};

UENUM(BlueprintType)
enum class DerivedStatsEnum : uint8
{
	EAttack					UMETA(DisplayName = "Attack"),
	EAttackChance			UMETA(DisplayName = "AttackChance"),
	EDefense				UMETA(DisplayName = "Defense"),
	EDefenseChance			UMETA(DisplayName = "DefenseChance"),
	EMagicPower				UMETA(DisplayName = "MagicPower"),
	EMagicResistance		UMETA(DisplayName = "MagicResistance"),
	EFireResistance			UMETA(DisplayName = "FireMagicResistance"),
	EIceResistance			UMETA(DisplayName = "IceMagicResistance"),
	EThunderResistance		UMETA(DisplayName = "ThunderMagicResistance"),
	EWindResistance			UMETA(DisplayName = "WindMagicResistance"),
	EWaterResistance		UMETA(DisplayName = "WaterMagicResistance"),
	EEarthResistance		UMETA(DisplayName = "EarthMagicResistance"),
	ELightResistance		UMETA(DisplayName = "LightMagicResistance"),
	EDarkResistance			UMETA(DisplayName = "DarkMagicResistance"),
};
