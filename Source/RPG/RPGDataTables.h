// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
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