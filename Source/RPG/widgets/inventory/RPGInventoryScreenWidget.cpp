// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGInventoryScreenWidget.h"

#include "UMG/Public/Components/Button.h"
#include "UMG/Public/Components/HorizontalBox.h"
#include "UMG/Public/Components/Image.h"
#include "UMG/Public/Components/TextBlock.h"
#include "UMG/Public/Components/VerticalBox.h"
#include "UMG/Public/Components/WidgetSwitcher.h"

#include "RPG/RPGCustomFunctionLibrary.h"

#include "RPG/components/RPGInventoryManagerComponent.h"

void URPGInventoryScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!Button_Discard->OnClicked.IsBound())
		Button_Discard->OnClicked.AddDynamic(this, &URPGInventoryScreenWidget::OnPressed_ButtonDiscard);

	if (!Button_Use->OnClicked.IsBound())
		Button_Use->OnClicked.AddDynamic(this, &URPGInventoryScreenWidget::OnPressed_ButtonUse);

	if (!Button_CloseItemUse->OnClicked.IsBound())
		Button_CloseItemUse->OnClicked.AddDynamic(this, &URPGInventoryScreenWidget::OnPressed_ButtonCloseItemUse);

	//Gamepad
}

void URPGInventoryScreenWidget::OnPressed_ButtonDiscard()
{
	if (Button_Discard->GetIsEnabled())
	{
		if (InventoryManagerReference->IsValidLowLevel())
			InventoryManagerReference->ShowDiscardWindow();
	}
}

void URPGInventoryScreenWidget::OnPressed_ButtonUse()
{
	if (Button_Use->GetIsEnabled())
	{
		if (InventoryManagerReference->IsValidLowLevel())
			InventoryManagerReference->SelectItemToUse();
	}
}

void URPGInventoryScreenWidget::OnPressed_ButtonCloseItemUse()
{
	WidgetSwitcher_UseItem->SetActiveWidgetIndex(0);
	HorizontalBox_ItemButtons->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void URPGInventoryScreenWidget::UpdateItemDetails_Implementation(FText& InItemName, ItemTypeEnum InItemType, ItemRarityEnum InItemRarity, FText& InItemDescription)
{
	TextBlock_ItemName->SetText(InItemName);
	TextBlock_ItemType->SetText(URPGCustomFunctionLibrary::ItemTypeToText(InItemType));
	TextBlock_ItemRarity->SetText(URPGCustomFunctionLibrary::ItemRarityToText(InItemRarity));
	TextBlock_ItemDescription->SetText(InItemDescription);

	TextBlock_ItemName->SetColorAndOpacity(FSlateColor::FSlateColor(URPGCustomFunctionLibrary::ItemRarityToColor(InItemRarity)));
	TextBlock_ItemType->SetColorAndOpacity(FSlateColor::FSlateColor(URPGCustomFunctionLibrary::ItemRarityToColor(InItemRarity)));
	TextBlock_ItemRarity->SetColorAndOpacity(FSlateColor::FSlateColor(URPGCustomFunctionLibrary::ItemRarityToColor(InItemRarity)));
}

void URPGInventoryScreenWidget::HighlightNewInventoryButton_Implementation(class UButton* InButton)
{
	UnhighlightInventoryButton();

	HighlightInventoryButton = InButton;
	HighlightInventoryButton->SetBackgroundColor(FLinearColor::FromSRGBColor(FColor::FromHex("#FFBC0066")));
}

void URPGInventoryScreenWidget::UnhighlightInventoryButton_Implementation()
{
	if (HighlightInventoryButton->IsValidLowLevel())
		HighlightInventoryButton->SetBackgroundColor(FLinearColor::FromSRGBColor(FColor::FromHex("#FFFFFF66")));
}