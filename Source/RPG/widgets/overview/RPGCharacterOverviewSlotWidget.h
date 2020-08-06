// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "RPG/enums/RPGStatTypeEnum.h"
#include "RPG/enums/RPGItemTypeEnum.h"

#include "RPG/structs/RPGBaseItemStruct.h"

#include "RPGCharacterOverviewSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URPGCharacterOverviewSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
	void NativePreConstruct();

public:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_CharacterName;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_CharacterLevel;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_CharacterExp;

	UPROPERTY(meta = (BindWidget))
		class UImage* Image_CharacterIcon;

	UPROPERTY(meta = (BindWidget))
		class URPGStatSlotWidget* StatSlot_HP;

	UPROPERTY(meta = (BindWidget))
		class URPGStatSlotWidget* StatSlot_MP;

	UPROPERTY(meta = (BindWidget))
		class URPGStatSlotWidget* StatSlot_Vitality;

	UPROPERTY(meta = (BindWidget))
		class URPGStatSlotWidget* StatSlot_Magic;

	UPROPERTY(meta = (BindWidget))
		class URPGStatSlotWidget* StatSlot_Spirit;

	UPROPERTY(meta = (BindWidget))
		class URPGStatSlotWidget* StatSlot_Strength;

	UPROPERTY(meta = (BindWidget))
		class URPGStatSlotWidget* StatSlot_Dexterity;

	UPROPERTY(meta = (BindWidget))
		class URPGStatSlotWidget* StatSlot_Luck;

	UPROPERTY(meta = (BindWidget))
		class URPGStatSlotWidget* StatSlot_Initiative;

	UPROPERTY(meta = (BindWidget))
		class URPGEquipmentSlotWidget* EquipmentSlot_Weapon;

	UPROPERTY(meta = (BindWidget))
		class URPGEquipmentSlotWidget* EquipmentSlot_Armor;

	UPROPERTY(meta = (BindWidget))
		class URPGEquipmentSlotWidget* EquipmentSlot_Accessory;

	UFUNCTION(BlueprintNativeEvent)
		void UpdateCharacterMainInfo(FName& InCharacterName, FText& InCharacterDisplayName, int32 InCharacterLevel, int32 InCharacterCurrentExp/*, image*/);

	UFUNCTION(BlueprintNativeEvent)
		void UpdateCharacterStats(TMap<StatsEnum, float>& InCharacterStats);

	UFUNCTION(BlueprintNativeEvent)
		void UpdateCharacterEquipment(TMap<ItemTypeEnum, FBaseItemStruct>& InCharacterEquipment);

private:
	UPROPERTY()
		TArray<class URPGStatSlotWidget*> CharacterStatSlots;

	UPROPERTY()
		TArray<class URPGEquipmentSlotWidget*> CharacterEquipmentSlots;
};
