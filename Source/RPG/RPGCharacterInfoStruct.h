#pragma once

#include "CoreMinimal.h"
#include "RPGCharacterStatsEnum.h"
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
		TMap<CharacterStatsEnum, float> Stats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<CharacterDerivedStatsEnum, float> DerivedStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* Icon;

	FCharacterInfoStruct()
	{
		CharacterName = "";
		DisplayName = FText::FromString("");

		CurrentExperience = 0;
		CurrentLevel = 1;
		CurrentHP = 0;
		CurrentMP = 0;

		Stats.FindOrAdd(CharacterStatsEnum::EMaxHP, 0);
		Stats.FindOrAdd(CharacterStatsEnum::EMaxMP, 0);
		Stats.FindOrAdd(CharacterStatsEnum::EStrength, 0);
		Stats.FindOrAdd(CharacterStatsEnum::EDexterity, 0);
		Stats.FindOrAdd(CharacterStatsEnum::EVitality, 0);
		Stats.FindOrAdd(CharacterStatsEnum::EMagic, 0);
		Stats.FindOrAdd(CharacterStatsEnum::ESpirit, 0);
		Stats.FindOrAdd(CharacterStatsEnum::ELuck, 0);
		Stats.FindOrAdd(CharacterStatsEnum::EInitiative, 0);

		DerivedStats.FindOrAdd(CharacterDerivedStatsEnum::EAttack, 0);
		DerivedStats.FindOrAdd(CharacterDerivedStatsEnum::EAttackChance, 0);
		DerivedStats.FindOrAdd(CharacterDerivedStatsEnum::EDefense, 0);
		DerivedStats.FindOrAdd(CharacterDerivedStatsEnum::EDefenseChance, 0);
		DerivedStats.FindOrAdd(CharacterDerivedStatsEnum::EMagicPower, 0);
		DerivedStats.FindOrAdd(CharacterDerivedStatsEnum::EMagicResistance, 0);
		DerivedStats.FindOrAdd(CharacterDerivedStatsEnum::EFireResistance, 0);
		DerivedStats.FindOrAdd(CharacterDerivedStatsEnum::EIceResistance, 0);
		DerivedStats.FindOrAdd(CharacterDerivedStatsEnum::EThunderResistance, 0);
		DerivedStats.FindOrAdd(CharacterDerivedStatsEnum::EWindResistance, 0);
		DerivedStats.FindOrAdd(CharacterDerivedStatsEnum::EWaterResistance, 0);
		DerivedStats.FindOrAdd(CharacterDerivedStatsEnum::EEarthResistance, 0);
		DerivedStats.FindOrAdd(CharacterDerivedStatsEnum::ELightResistance, 0);
		DerivedStats.FindOrAdd(CharacterDerivedStatsEnum::EDarkResistance, 0);

		//Icon;
	}
};