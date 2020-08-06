// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGEquipmentSlotWidget.h"

#include "UMG/Public/Components/Image.h"
#include "UMG/Public/Components/ScaleBox.h"
#include "UMG/Public/Components/TextBlock.h"

#include "RPG/RPGCustomFunctionLibrary.h"

void URPGEquipmentSlotWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	//Image_Icon->SetBrushFromTexture(URPGCustomFunctionLibrary::StatTypeToImage(AssignedItemType), false);

	ScaleBox_SlotSize->SetUserSpecifiedScale((float)SlotSize / 26.f);

	TextBlock_ItemName->Font.Size = SlotSize;
}

void URPGEquipmentSlotWidget::UpdateSlotInfo_Implementation(FBaseItemStruct Item)
{
	if (Item.ItemName != "None")
	{
		TextBlock_ItemName->SetText(Item.DisplayName);
		TextBlock_ItemName->SetColorAndOpacity(URPGCustomFunctionLibrary::ItemRarityToColor(Item.Rarity));

		Image_Icon->SetBrushFromTexture(Item.Icon, false);
	}
	else
	{
		TextBlock_ItemName->SetText(FText::FromString("-"));
		TextBlock_ItemName->SetColorAndOpacity(FLinearColor::FromSRGBColor(FColor::FromHex("#FFFFFFFF")));

		//Image_Icon->SetBrushFromTexture(URPGCustomFunctionLibrary::StatTypeToText(AssignedItemType), false);
	}
}