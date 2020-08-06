// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"

#include "RPG/enums/RPGActionTypeEnum.h"
#include "RPG/enums/RPGItemRarityEnum.h"
#include "RPG/enums/RPGItemTypeEnum.h"
#include "RPG/enums/RPGStatTypeEnum.h"

#include "RPGDataTables.generated.h"

USTRUCT(BlueprintType)
struct FHeroesTable : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 Hero1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 Hero2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 Hero3;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 Hero4;
};

USTRUCT(BlueprintType)
struct FEncountersTable : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TMap<int, FName> Enemies;
};

USTRUCT(BlueprintType)
struct FEnemiesTable : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FName Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 Level;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 ExperienceReward;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 GoldReward;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TMap<StatsEnum, float> Stats;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TMap<DerivedStatsEnum, float> DerivedStats;

//    UPROPERTY(EditAnywhere, BlueprintReadWrite)
//      PossibleLoot;
};

USTRUCT(BlueprintType)
struct FItemsTable : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FName Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        ItemTypeEnum ItemType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        ItemRarityEnum ItemRarity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool bCanBeUsedInBattle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool bCanBeUsedInInventory;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 MaxStackAmount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 BuyValue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 SellValue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TMap<StatsEnum, float> Stats;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TMap<DerivedStatsEnum, float> DerivedStats;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        class UTexture2D* Icon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool bCanBeBought;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool bCanBeSold;
};

USTRUCT(BlueprintType)
struct FActionsTable : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FName Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        ActionTypeEnum ActionType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float BaseCostMP;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float BaseCostHP;
};