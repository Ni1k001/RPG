// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGCharacterOverviewSlotWidget.h"
#include "UMG/Public/Components/TextBlock.h"
#include "UMG/Public/Components/Image.h"

#include "RPG/widgets/overview/RPGEquipmentSlotWidget.h"
#include "RPG/widgets/overview/RPGStatSlotWidget.h"

#include "RPG/RPGCustomFunctionLibrary.h"

void URPGCharacterOverviewSlotWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	CharacterStatSlots.Add(StatSlot_HP);
	CharacterStatSlots.Add(StatSlot_MP);
	CharacterStatSlots.Add(StatSlot_Vitality);
	CharacterStatSlots.Add(StatSlot_Magic);
	CharacterStatSlots.Add(StatSlot_Spirit);
	CharacterStatSlots.Add(StatSlot_Strength);
	CharacterStatSlots.Add(StatSlot_Dexterity);
	CharacterStatSlots.Add(StatSlot_Luck);
	CharacterStatSlots.Add(StatSlot_Initiative);

	CharacterEquipmentSlots.Add(EquipmentSlot_Weapon);
	CharacterEquipmentSlots.Add(EquipmentSlot_Armor);
	CharacterEquipmentSlots.Add(EquipmentSlot_Accessory);
}

void URPGCharacterOverviewSlotWidget::UpdateCharacterMainInfo_Implementation(FName& InCharacterName, FText& InCharacterDisplayName, int32 InCharacterLevel, int32 InCharacterCurrentExp/*, image*/)
{
	TextBlock_CharacterName->SetText(InCharacterDisplayName);
	TextBlock_CharacterLevel->SetText(FText::FromString("Level " + FString::FromInt(InCharacterLevel)));
	TextBlock_CharacterExp->SetText(FText::FromString("Current: " + FString::FromInt(InCharacterCurrentExp) + " / Next: " + FString::FromInt(URPGCustomFunctionLibrary::GetExperienceNeededToNextLevel(InCharacterName, InCharacterLevel, InCharacterCurrentExp))));
}

void URPGCharacterOverviewSlotWidget::UpdateCharacterStats_Implementation(TMap<StatsEnum, float>& InCharacterStats)
{
	for (int i = 0; i < CharacterStatSlots.Num(); i++)
	{
		CharacterStatSlots[i]->TextBlock_StatName->SetText(URPGCustomFunctionLibrary::StatTypeToText(CharacterStatSlots[i]->AssignedStatType));
		CharacterStatSlots[i]->TextBlock_StatValue->SetText(FText::FromString(FString::SanitizeFloat(*InCharacterStats.Find(CharacterStatSlots[i]->AssignedStatType))));
	}
}

void URPGCharacterOverviewSlotWidget::UpdateCharacterEquipment_Implementation(TMap<ItemTypeEnum, FBaseItemStruct>& InCharacterEquipment)
{
	for (int i = 0; i < CharacterEquipmentSlots.Num(); i++)
		CharacterEquipmentSlots[i]->UpdateSlotInfo(*InCharacterEquipment.Find(CharacterEquipmentSlots[i]->AssignedItemType));
}