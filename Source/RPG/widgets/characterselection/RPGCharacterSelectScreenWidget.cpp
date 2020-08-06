// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGCharacterSelectScreenWidget.h"
#include "UMG/Public/Components/Button.h"
#include "UMG/Public/Components/TextBlock.h"
#include "UMG/Public/Components/VerticalBox.h"
#include "UMG/Public/Components/WidgetSwitcher.h"
#include "UMG/Public/Components/WrapBox.h"

#include "RPG/widgets/characterselection/RPGCharacterEquipmentSlotWidget.h"
#include "RPG/widgets/overview/RPGStatSlotWidget.h"

void URPGCharacterSelectScreenWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	StatSlotsReference.Add(StatSlot_HP);
	StatSlotsReference.Add(StatSlot_MP);
	StatSlotsReference.Add(StatSlot_Vitality);
	StatSlotsReference.Add(StatSlot_Magic);
	StatSlotsReference.Add(StatSlot_Spirit);
	StatSlotsReference.Add(StatSlot_Strength);
	StatSlotsReference.Add(StatSlot_Dexterity);
	StatSlotsReference.Add(StatSlot_Luck);
	StatSlotsReference.Add(StatSlot_Initiative);

	EquipmentSlotsReference.Add(CharacterEquipmentSlot_Weapon);
	EquipmentSlotsReference.Add(CharacterEquipmentSlot_Armor);
	EquipmentSlotsReference.Add(CharacterEquipmentSlot_Accessory);
}

void URPGCharacterSelectScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	for (int i = 0; i < EquipmentSlotsReference.Num(); i++)
		if (EquipmentSlotsReference[i]->IsValidLowLevel())
			EquipmentSlotsReference[i]->SetCharacterSelectionScreenReference(this);
}

TArray<URPGStatSlotWidget*> URPGCharacterSelectScreenWidget::GetStatSlotsReference()
{
	return StatSlotsReference;
}

void URPGCharacterSelectScreenWidget::SetStatSlotsReference(TArray<URPGStatSlotWidget*> InStatSlotsReference)
{
	StatSlotsReference = InStatSlotsReference;
}

TArray<URPGCharacterEquipmentSlotWidget*> URPGCharacterSelectScreenWidget::GetEquipmentSlotsReference()
{
	return EquipmentSlotsReference;
}

void URPGCharacterSelectScreenWidget::SetEquipmentSlotsReference(TArray<URPGCharacterEquipmentSlotWidget*> InEquipmentSlotsReference)
{
	EquipmentSlotsReference = InEquipmentSlotsReference;
}

/*
UButton* URPGCharacterSelectScreenWidget::GetHighlightEquipmentChangeButtonReference();
void URPGCharacterSelectScreenWidget::SetHighlightEquipmentChangeButtonReference(UButton* InHighlightEquipmentChangeButtonReference);
UButton* URPGCharacterSelectScreenWidget::GetHighlightCharacterSelectionButtonReference();
void URPGCharacterSelectScreenWidget::SetHighlightCharacterSelectionButtonReference(UButton* InHighlightCharacterSelectionButtonReference);
UButton* URPGCharacterSelectScreenWidget::GetHighlightSelectEquipmentButtonReference();
void URPGCharacterSelectScreenWidget::SetHighlightSelectEquipmentButtonReference(UButton* InHighlightSelectEquipmentButtonReference);
*/

void URPGCharacterSelectScreenWidget::OnPressed_ButtonClose()
{
	UnhighlighteEquipmentChangeButton();

	WidgetSwitcher_Selection->SetActiveWidgetIndex(0);

	for (int i = 0; i < StatSlotsReference.Num(); i++)
		if (StatSlotsReference[i]->IsValidLowLevel())
			StatSlotsReference[i]->SetVisibility(ESlateVisibility::Hidden);
}

void URPGCharacterSelectScreenWidget::HighlightNewEquipmentChangeButton(class UButton* InButton)
{
	//Gamepad

	UnhighlighteEquipmentChangeButton();
	HighlightEquipmentChangeButtonReference = InButton;
	HighlightEquipmentChangeButtonReference->SetBackgroundColor(FLinearColor(FColor::FromHex("#FF7F0066")));
}

void URPGCharacterSelectScreenWidget::UnhighlighteEquipmentChangeButton()
{
	if (HighlightEquipmentChangeButtonReference->IsValidLowLevel())
		HighlightEquipmentChangeButtonReference->SetBackgroundColor(FLinearColor(FColor::FromHex("#FFFFFF66")));
}

void URPGCharacterSelectScreenWidget::HighlightNewCharacterSelectionButton(class UButton* InButton)
{
	//Gamepad

	UnhighlightCharacterSelectionButton();
	HighlightCharacterSelectionButtonReference = InButton;
	HighlightCharacterSelectionButtonReference->SetBackgroundColor(FLinearColor(FColor::FromHex("#FF7F0066")));
}

void URPGCharacterSelectScreenWidget::UnhighlightCharacterSelectionButton()
{
	if (HighlightCharacterSelectionButtonReference->IsValidLowLevel())
		HighlightCharacterSelectionButtonReference->SetBackgroundColor(FLinearColor(FColor::FromHex("#FFFFFF66")));
}

void URPGCharacterSelectScreenWidget::HighlightNewSelectEquipmentButton(class UButton* InButton)
{
	//Gamepad

	UnhighlightSelectEquipmentButton();
	HighlightSelectEquipmentButtonReference = InButton;
	HighlightSelectEquipmentButtonReference->SetBackgroundColor(FLinearColor(FColor::FromHex("#FF7F0066")));
}

void URPGCharacterSelectScreenWidget::UnhighlightSelectEquipmentButton()
{
	if (HighlightSelectEquipmentButtonReference->IsValidLowLevel())
		HighlightSelectEquipmentButtonReference->SetBackgroundColor(FLinearColor(FColor::FromHex("#FFFFFF66")));
}