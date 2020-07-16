// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGBattleCharacterSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URPGBattleCharacterSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
		class URPGBattleCharacterStatsComponent* CharacterStatsComponentRef;

	UPROPERTY(meta = (BindWidget))
		class UBorder* Border_Highlight;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* ProgressBar_HP;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* ProgressBar_Initiative;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* ProgressBar_MP;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_CharacterName;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_HPValue;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_MPValue;

	UFUNCTION(BlueprintNativeEvent)
		void UpdateHealthValue(float InCurrent, float InMax);

	UFUNCTION(BlueprintNativeEvent)
		void UpdateManaValue(float InCurrent, float InMax);

	UFUNCTION(BlueprintNativeEvent)
		void UpdateInitiativeValue(float InCurrent, float InMax);

	UFUNCTION(BlueprintNativeEvent)
		void UpdateCharacterDisplayName(const FText& InCharacterDisplayName);

	UFUNCTION(BlueprintNativeEvent)
		void HighlightSlot();

	UFUNCTION(BlueprintNativeEvent)
		void UnhighlightSlot();

	UFUNCTION(BlueprintNativeEvent)
		void DarkenSlotOnDeath();

	UFUNCTION(BlueprintNativeEvent)
		void RestoreSlotOnResurrection();
};
