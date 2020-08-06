#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "Templates/SharedPointer.h"

#include "RPG/enums/RPGItemTypeEnum.h"
#include "RPG/enums/RPGStatTypeEnum.h"

#include "RPG/structs/RPGBaseItemStruct.h"

#include "RPGCharacterInfoStruct.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FCharacterInfoStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "100000", UIMin = "0", UIMax = "100000"))
		int32 CurrentExperience;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1", ClampMax = "99", UIMin = "1", UIMax = "99"))
		int32 CurrentLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "100000", UIMin = "0", UIMax = "100000"))
		float CurrentHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "100000", UIMin = "0", UIMax = "100000"))
		float CurrentMP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<StatsEnum, float> Stats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<DerivedStatsEnum, float> DerivedStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ARPGBattleCharacter* BattleCharacterClass;

//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<ItemTypeEnum, FBaseItemStruct> Equipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* Icon;

	//Actions
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ActionPoints;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<FName, int32> CharacterActions;

	FCharacterInfoStruct()
	{
		Name = "";
		DisplayName = FText::FromString("");

		CurrentExperience = 0;
		CurrentLevel = 1;
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

		FBaseItemStruct Item;

		Item.Type = ItemTypeEnum::EWeapon;
		Equipment.FindOrAdd(ItemTypeEnum::EWeapon, Item);

		Item.Type = ItemTypeEnum::EArmor;
		Equipment.FindOrAdd(ItemTypeEnum::EArmor, Item);

		Item.Type = ItemTypeEnum::EAccessory;
		Equipment.FindOrAdd(ItemTypeEnum::EAccessory, Item);

		Item.Type = ItemTypeEnum::EConsumable;
		Equipment.FindOrAdd(ItemTypeEnum::EConsumable, Item);

		Item.Type = ItemTypeEnum::EMiscellaneous;
		Equipment.FindOrAdd(ItemTypeEnum::EMiscellaneous, Item);

		Item.Type = ItemTypeEnum::EKeyItem;
		Equipment.FindOrAdd(ItemTypeEnum::EKeyItem, Item);

		//Icon;

		ActionPoints = 0;

		CharacterActions.FindOrAdd("Attack", 1);
		CharacterActions.FindOrAdd("Defend", 1);
		CharacterActions.FindOrAdd("Items", 1);
		CharacterActions.FindOrAdd("Flee", 1);
	}
};