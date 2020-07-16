// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPG/enums/RPGActionTypeEnum.h"
#include "RPG/enums/RPGItemRarityEnum.h"
#include "RPG/enums/RPGItemTypeEnum.h"
#include "RPG/enums/RPGStatTypeEnum.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RPGCustomFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URPGCustomFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
    /*				Conversion				*/
    UFUNCTION(BlueprintCallable, Category = "Custom")
        static FText ActionTypeToText(ActionTypeEnum InActionType);

    UFUNCTION(BlueprintCallable, Category = "Custom")
        static FText ItemTypeToText(ItemTypeEnum InItemType);

    /*    UFUNCTION(BlueprintCallable)
            ItemTypeToImage(ItemTypeEnum InItemType);*/

    UFUNCTION(BlueprintCallable, Category = "Custom")
        static FText ItemRarityToText(ItemRarityEnum InItemRarity);

    UFUNCTION(BlueprintCallable, Category = "Custom")
        static FColor ItemRarityToColor(ItemRarityEnum InItemRarity);

    UFUNCTION(BlueprintCallable, Category = "Custom")
        static FText StatTypeToText(StatsEnum InStatType);

    UFUNCTION(BlueprintCallable, Category = "Custom")
        static FText DerivedStatTypeToText(DerivedStatsEnum InDerivedStatType);

    /*				Stats				    */
    UFUNCTION(BlueprintCallable, Category = "Custom")
        static int32 GetExperienceNeededToNextLevel(FName InHeroName, int32 InCurrentLevel, int32 InCurrentXP);

    /*				SaveAndLoad				*/
/*    UFUNCTION(BlueprintCallable, Category = "Custom")
        static void ChangeMap(AActor* InCharacter, FName InMapName, FName InSpawnPointName);*/

    /*				DisplayName				*/
    UFUNCTION(BlueprintCallable, Category = "Custom")
        static FText GetActionDisplayName(FName InActionName);

    UFUNCTION(BlueprintCallable, Category = "Custom")
        static FText GetItemDisplayName(FName InItemName);
};
