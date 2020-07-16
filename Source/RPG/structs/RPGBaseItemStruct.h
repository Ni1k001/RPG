// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPG/enums/RPGItemTypeEnum.h"
#include "RPG/enums/RPGItemRarityEnum.h"
#include "RPG/enums/RPGStatTypeEnum.h"
#include "Engine/UserDefinedStruct.h"
#include "RPGBaseItemStruct.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FBaseItemStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ItemTypeEnum Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ItemRarityEnum Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bCanBeUsedInBattle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bCanBeUsedInInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "99", UIMin = "0", UIMax = "99"))	// 0 - unlimited (max of int32 value)
		int32 MaxStackAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "999999", UIMin = "0", UIMax = "999999"))
		int32 BuyValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "999999", UIMin = "0", UIMax = "999999"))
		int32 SellValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<StatsEnum, float> Stats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<DerivedStatsEnum, float> DerivedStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* Icon;

	FBaseItemStruct()
	{
		ItemName = "";
		DisplayName = FText::FromString("");

		Type = ItemTypeEnum::EMeleeWeapon;
		Rarity = ItemRarityEnum::ECommon;
		bCanBeUsedInBattle = false;
		bCanBeUsedInInventory = false;

		MaxStackAmount = 0;
		BuyValue = 0;
		SellValue = 0;

		Stats.FindOrAdd(StatsEnum::EHP, 0);
		Stats.FindOrAdd(StatsEnum::EMP, 0);
		Stats.FindOrAdd(StatsEnum::EStrength, 0);
		Stats.FindOrAdd(StatsEnum::EDexterity, 0);
		Stats.FindOrAdd(StatsEnum::EVitality, 0);
		Stats.FindOrAdd(StatsEnum::EMagic, 0);
		Stats.FindOrAdd(StatsEnum::ESpirit, 0);
		Stats.FindOrAdd(StatsEnum::ELuck, 0);
		Stats.FindOrAdd(StatsEnum::EInitiative, 0);

		DerivedStats.FindOrAdd(DerivedStatsEnum::EAttack, 0);
		DerivedStats.FindOrAdd(DerivedStatsEnum::EAttackChance, 0);
		DerivedStats.FindOrAdd(DerivedStatsEnum::EDefense, 0);
		DerivedStats.FindOrAdd(DerivedStatsEnum::EDefenseChance, 0);
		DerivedStats.FindOrAdd(DerivedStatsEnum::EMagicPower, 0);
		DerivedStats.FindOrAdd(DerivedStatsEnum::EMagicResistance, 0);
		DerivedStats.FindOrAdd(DerivedStatsEnum::EFireResistance, 0);
		DerivedStats.FindOrAdd(DerivedStatsEnum::EIceResistance, 0);
		DerivedStats.FindOrAdd(DerivedStatsEnum::EThunderResistance, 0);
		DerivedStats.FindOrAdd(DerivedStatsEnum::EWindResistance, 0);
		DerivedStats.FindOrAdd(DerivedStatsEnum::EWaterResistance, 0);
		DerivedStats.FindOrAdd(DerivedStatsEnum::EEarthResistance, 0);
		DerivedStats.FindOrAdd(DerivedStatsEnum::ELightResistance, 0);
		DerivedStats.FindOrAdd(DerivedStatsEnum::EDarkResistance, 0);

		Description = FText::FromString("");

		//Icon;
	}
};
