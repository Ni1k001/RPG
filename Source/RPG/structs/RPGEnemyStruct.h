// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPG/enums/RPGStatTypeEnum.h"
#include "Engine/UserDefinedStruct.h"
#include "RPGEnemyStruct.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FEnemyStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1", ClampMax = "99", UIMin = "1", UIMax = "99"))
		int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "100000", UIMin = "0", UIMax = "100000"))
		int32 ExperienceReward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "100000", UIMin = "0", UIMax = "100000"))
		int32 GoldReward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "100000", UIMin = "0", UIMax = "100000"))
		float CurrentHP; // ?

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "100000", UIMin = "0", UIMax = "100000"))
		float CurrentMP; // ?

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<StatsEnum, float> Stats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<DerivedStatsEnum, float> DerivedStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* Icon; // ?

	//Battle Actor Class
	//PossibleLoot
	//Actions ?

	FEnemyStruct()
	{
		Name = "";
		DisplayName = FText::FromString("");

		Level = 1;
		ExperienceReward = 0;
		GoldReward = 0;
		CurrentHP = 0;
		CurrentMP = 0;

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

		//Icon;
	}
};