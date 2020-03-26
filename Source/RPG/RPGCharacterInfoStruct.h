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
		FName CharacterName = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText DisplayName = FText::FromString("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "99", UIMin = "0", UIMax = "99"))
		int32 CurrentExperience = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1", ClampMax = "99", UIMin = "1", UIMax = "99"))
		int32 CurrentLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "100000", UIMin = "0", UIMax = "100000"))
		float CurrentHP = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "100000", UIMin = "0", UIMax = "100000"))
		float CurrentMP = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<CharacterStatsEnum, float> Stats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<CharacterDerivedStatsEnum, float> DerivedStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* Icon;
};