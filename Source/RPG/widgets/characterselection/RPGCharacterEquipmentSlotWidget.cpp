// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGCharacterEquipmentSlotWidget.h"
#include "UMG/Public/Components/Button.h"
#include "UMG/Public/Components/Image.h"
#include "UMG/Public/Components/ScaleBox.h"
#include "UMG/Public/Components/TextBlock.h"
#include "UMG/Public/Components/WidgetSwitcher.h"
#include "TimerManager.h"

#include "RPG/RPGCustomFunctionLibrary.h"

#include "RPG/components/RPGInventoryManagerComponent.h"

#include "RPG/widgets/characterselection/RPGCharacterSelectScreenWidget.h"

void URPGCharacterEquipmentSlotWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (!Button_ChangeEquipment->OnClicked.IsBound())
		Button_ChangeEquipment->OnClicked.AddDynamic(this, &URPGCharacterEquipmentSlotWidget::OnPressed_ButtonChangeEquipment);

	//Image_ItemIcon->SetBrushFromTexture(, false);

	ScaleBox_SlotSize->SetUserSpecifiedScale(float(SlotSize) / 26.f);

	TextBlock_ItemName->Font.Size = SlotSize;
}

ItemTypeEnum URPGCharacterEquipmentSlotWidget::GetAssignedItemType()
{
	return AssignedItemType;
}

void URPGCharacterEquipmentSlotWidget::SetAssignedItemType(ItemTypeEnum InAssignedItemType)
{
	AssignedItemType = InAssignedItemType;
}

int32 URPGCharacterEquipmentSlotWidget::GetSlotSize()
{
	return SlotSize;
}

void URPGCharacterEquipmentSlotWidget::SetSlotSize(int32 InSlotSize)
{
	SlotSize = InSlotSize;
}

 URPGCharacterSelectScreenWidget* URPGCharacterEquipmentSlotWidget::GetCharacterSelectionScreenReference()
{
	return CharacterSelectionScreenReference;
}

void URPGCharacterEquipmentSlotWidget::SetCharacterSelectionScreenReference(URPGCharacterSelectScreenWidget* InCharacterSelectionScreenReference)
{
	CharacterSelectionScreenReference = InCharacterSelectionScreenReference;
}

URPGInventoryManagerComponent* URPGCharacterEquipmentSlotWidget::GetInventoryManagerReference()
{
	return InventoryManagerReference;
}

void URPGCharacterEquipmentSlotWidget::SetInventoryManagerReference(URPGInventoryManagerComponent* InInventoryManagerReference)
{
	InventoryManagerReference = InInventoryManagerReference;
}

bool URPGCharacterEquipmentSlotWidget::GetBIsDoublePressed()
{
	return bIsDoublePressed;
}

void URPGCharacterEquipmentSlotWidget::SetBIsDoublePressed(bool InBIsDoublePressed)
{
	bIsDoublePressed = InBIsDoublePressed;
}

void URPGCharacterEquipmentSlotWidget::OnPressed_ButtonChangeEquipment()
{
	if (bIsDoublePressed)
	{
		URPGInventoryManagerComponent* IMC = Cast<URPGInventoryManagerComponent>(GetWorld()->GetFirstPlayerController()->GetComponentByClass(URPGInventoryManagerComponent::StaticClass()));

		IMC->UnequipItem(AssignedItemType);
		IMC->ShowAllEquipableItems(AssignedItemType);
	}
	else
	{
		if (CharacterSelectionScreenReference->IsValidLowLevel())
		{
			CharacterSelectionScreenReference->WidgetSwitcher_Selection->SetActiveWidgetIndex(1);

			URPGInventoryManagerComponent* IMC = Cast<URPGInventoryManagerComponent>(GetWorld()->GetFirstPlayerController()->GetComponentByClass(URPGInventoryManagerComponent::StaticClass()));

			IMC->ShowAllEquipableItems(AssignedItemType);
			
			CharacterSelectionScreenReference->HighlightNewEquipmentChangeButton(Button_ChangeEquipment);
		}

		bIsDoublePressed = true;

		FTimerDelegate TimerDelegate;
		FTimerHandle TimerHandle;
		bool TimerVar = false;
		TimerDelegate.BindUFunction(this, FName("SetBIsDoublePressed"), TimerVar);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 1.f, false, 0.25f);
	}
}

void URPGCharacterEquipmentSlotWidget::UpdateSlotInfo(FBaseItemStruct InItem)
{
	if (InItem.ItemName != "None")
	{
		TextBlock_ItemName->SetText(InItem.DisplayName);
		TextBlock_ItemName->SetColorAndOpacity(URPGCustomFunctionLibrary::ItemRarityToColor(InItem.Rarity));
		Image_ItemIcon->SetBrushFromTexture(InItem.Icon, false);
	}
	else
	{
		TextBlock_ItemName->SetText(FText::FromString("-"));
		TextBlock_ItemName->SetColorAndOpacity(FLinearColor::FLinearColor(FColor::FromHex("#FFFFFFFF")));
		//Image_ItemIcon->SetBrushFromTexture(URPGCustomFunctionLibrary::, false);
	}
}