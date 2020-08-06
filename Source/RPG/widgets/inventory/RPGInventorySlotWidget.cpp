// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGInventorySlotWidget.h"

#include "UMG/Public/Components/Button.h"
#include "UMG/Public/Components/Image.h"
#include "UMG/Public/Components/TextBlock.h"

#include "RPG/RPGCustomFunctionLibrary.h"

#include "RPG/components/RPGInventoryManagerComponent.h"

#include "RPG/widgets/inventory/RPGInventoryScreenWidget.h"

void URPGInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!Button_InventorySlot->OnClicked.IsBound())
		Button_InventorySlot->OnClicked.AddDynamic(this, &URPGInventorySlotWidget::OnPressed);
}

void URPGInventorySlotWidget::OnPressed() //TODO
{
	if (InventoryManagerReference->IsValidLowLevel())
	{
		InventoryManagerReference->SetSelectedItemSlot(InventoryManagerReference->GetInventorySlotsReference().Find(this));

		InventoryManagerReference->RefreshItemDetails();

		InventoryManagerReference->GetInventoryScreenReference()->HighlightNewInventoryButton(Button_InventorySlot);
	}
}

void URPGInventorySlotWidget::UpdateItemData_Implementation(int32 InCurrentStackAmount, FBaseItemStruct InItem)
{
	TextBlock_Amount->SetText(FText::FromString(FString::FromInt(InCurrentStackAmount)));

	TextBlock_ItemName->SetText(InItem.DisplayName);

	TextBlock_ItemName->SetColorAndOpacity(FSlateColor::FSlateColor(URPGCustomFunctionLibrary::ItemRarityToColor(InItem.Rarity)));

	SetVisibility(ESlateVisibility::Visible);

	Image_ItemIcon->SetBrushFromTexture(InItem.Icon);
}