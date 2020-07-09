#pragma once

#include "CoreMinimal.h"
#include "RPGStatTypeEnum.h"
#include "Engine/UserDefinedStruct.h"
#include "RPGCharacterInfoStruct.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FCharacterInfoStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "99", UIMin = "0", UIMax = "99"))
		int32 CurrentExperience;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1", ClampMax = "99", UIMin = "1", UIMax = "99"))
		int32 CurrentLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "100000", UIMin = "0", UIMax = "100000"))
		float CurrentHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "100000", UIMin = "0", UIMax = "100000"))
		float CurrentMP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<StatsEnum, float> CharacterStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<DerivedStatsEnum, float> CharacterDerivedStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* Icon;

	//Battle Actor Class
	//Equipment
	//Actions

	FCharacterInfoStruct()
	{
		CharacterName = "";
		DisplayName = FText::FromString("");

		CurrentExperience = 0;
		CurrentLevel = 1;
		CurrentHP = 0;
		CurrentMP = 0;

		CharacterStats.FindOrAdd(StatsEnum::EHP, 0);
		CharacterStats.FindOrAdd(StatsEnum::EMP, 0);
		CharacterStats.FindOrAdd(StatsEnum::EStrength, 0);
		CharacterStats.FindOrAdd(StatsEnum::EDexterity, 0);
		CharacterStats.FindOrAdd(StatsEnum::EVitality, 0);
		CharacterStats.FindOrAdd(StatsEnum::EMagic, 0);
		CharacterStats.FindOrAdd(StatsEnum::ESpirit, 0);
		CharacterStats.FindOrAdd(StatsEnum::ELuck, 0);
		CharacterStats.FindOrAdd(StatsEnum::EInitiative, 0);

		CharacterDerivedStats.FindOrAdd(DerivedStatsEnum::EAttack, 0);
		CharacterDerivedStats.FindOrAdd(DerivedStatsEnum::EAttackChance, 0);
		CharacterDerivedStats.FindOrAdd(DerivedStatsEnum::EDefense, 0);
		CharacterDerivedStats.FindOrAdd(DerivedStatsEnum::EDefenseChance, 0);
		CharacterDerivedStats.FindOrAdd(DerivedStatsEnum::EMagicPower, 0);
		CharacterDerivedStats.FindOrAdd(DerivedStatsEnum::EMagicResistance, 0);
		CharacterDerivedStats.FindOrAdd(DerivedStatsEnum::EFireResistance, 0);
		CharacterDerivedStats.FindOrAdd(DerivedStatsEnum::EIceResistance, 0);
		CharacterDerivedStats.FindOrAdd(DerivedStatsEnum::EThunderResistance, 0);
		CharacterDerivedStats.FindOrAdd(DerivedStatsEnum::EWindResistance, 0);
		CharacterDerivedStats.FindOrAdd(DerivedStatsEnum::EWaterResistance, 0);
		CharacterDerivedStats.FindOrAdd(DerivedStatsEnum::EEarthResistance, 0);
		CharacterDerivedStats.FindOrAdd(DerivedStatsEnum::ELightResistance, 0);
		CharacterDerivedStats.FindOrAdd(DerivedStatsEnum::EDarkResistance, 0);

		//Icon;
	}
};