// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGChangeEquipmentSlotWidget.h"
#include "UMG/Public/Components/Button.h"
#include "UMG/Public/Components/Image.h"
#include "UMG/Public/Components/ScaleBox.h"
#include "UMG/Public/Components/TextBlock.h"
#include "TimerManager.h"

#include "RPG/RPGCustomFunctionLibrary.h"

#include "RPG/components/RPGInventoryManagerComponent.h"

#include "RPG/widgets/characterselection/RPGCharacterSelectScreenWidget.h"

void URPGChangeEquipmentSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!Button_ChangeEquipment->OnClicked.IsBound())
		Button_ChangeEquipment->OnClicked.AddDynamic(this, &URPGChangeEquipmentSlotWidget::OnPressed_ButtonChangeEquipment);
}

FName URPGChangeEquipmentSlotWidget::GetAssignedItemName()
{
	return AssignedItemName;
}

void URPGChangeEquipmentSlotWidget::SetAssignedItemName(FName InAssignedItemName)
{
	AssignedItemName = InAssignedItemName;
}

URPGInventoryManagerComponent* URPGChangeEquipmentSlotWidget::GetInventoryManagerReference()
{
	return InventoryManagerReference;
}

void URPGChangeEquipmentSlotWidget::SetInventoryManagerReference(URPGInventoryManagerComponent* InInventoryManagerReference)
{
	InventoryManagerReference = InInventoryManagerReference;
}

URPGCharacterSelectScreenWidget* URPGChangeEquipmentSlotWidget::GetCharacterSelectionScreenReference()
{
	return CharacterSelectionScreenReference;
}

void URPGChangeEquipmentSlotWidget::SetCharacterSelectionScreenReference(URPGCharacterSelectScreenWidget* InCharacterSelectionScreenReference)
{
	CharacterSelectionScreenReference = InCharacterSelectionScreenReference;
}

bool URPGChangeEquipmentSlotWidget::GetBIsDoublePressed()
{
	return bIsDoublePressed;
}

void URPGChangeEquipmentSlotWidget::SetBIsDoublePressed(bool InBIsDoublePressed)
{
	bIsDoublePressed = InBIsDoublePressed;
}

void URPGChangeEquipmentSlotWidget::OnPressed_ButtonChangeEquipment()
{
	if (bIsDoublePressed)
	{
		if (InventoryManagerReference->IsValidLowLevel())
		{
			InventoryManagerReference->EquipItem(AssignedItemName);
			bIsDoublePressed = false;
		}
	}
	else
	{
		if (InventoryManagerReference->IsValidLowLevel())
		{
			InventoryManagerReference->CalculateStatsComparisonOnEquip(AssignedItemName);
			if (CharacterSelectionScreenReference->IsValidLowLevel())
			{
				CharacterSelectionScreenReference->HighlightNewSelectEquipmentButton(Button_ChangeEquipment);
			}
		}

		bIsDoublePressed = true;

		FTimerDelegate TimerDelegate;
		FTimerHandle TimerHandle;
		bool TimerVar = false;
		TimerDelegate.BindUFunction(this, FName("SetBIsDoublePressed"), TimerVar);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 1.f, false, 0.25f);
	}
}

void URPGChangeEquipmentSlotWidget::UpdateSlotInfo(FBaseItemStruct InItem)
{
	AssignedItemName = InItem.ItemName;

	if (InItem.ItemName != "None")
	{
		TextBlock_ItemName->SetText(InItem.DisplayName);
		TextBlock_ItemName->SetColorAndOpacity(URPGCustomFunctionLibrary::ItemRarityToColor(InItem.Rarity));
		Image_DefaultIcon->SetBrushFromTexture(InItem.Icon, false);
	}
}