// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
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
};