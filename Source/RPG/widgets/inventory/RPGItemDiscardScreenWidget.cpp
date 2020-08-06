// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGItemDiscardScreenWidget.h"
#include "Kismet/KismetMathLibrary.h"

#include "UMG/Public/Components/Button.h"
#include "UMG/Public/Components/Image.h"
#include "UMG/Public/Components/Slider.h"
#include "UMG/Public/Components/TextBlock.h"

#include "RPG/components/RPGInventoryManagerComponent.h"

void URPGItemDiscardScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!Button_Cancel->OnClicked.IsBound())
		Button_Cancel->OnClicked.AddDynamic(this, &URPGItemDiscardScreenWidget::OnPressed_ButtonCancel);

	if (!Button_Discard->OnClicked.IsBound())
		Button_Discard->OnClicked.AddDynamic(this, &URPGItemDiscardScreenWidget::OnPressed_ButtonDiscard);

	if (!Slider_DiscardAmount->OnValueChanged.IsBound())
		Slider_DiscardAmount->OnValueChanged.AddDynamic(this, &URPGItemDiscardScreenWidget::OnValueChanged_SliderDiscardAmount);

	//Gamepad
}

void URPGItemDiscardScreenWidget::OnPressed_ButtonCancel()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void URPGItemDiscardScreenWidget::OnPressed_ButtonDiscard()
{
	SetVisibility(ESlateVisibility::Collapsed);

	if (InventoryManagerReference->IsValidLowLevel())
	{
		InventoryManagerReference->RemoveItemFromInventory(ItemToDiscard, AmountToDiscard);
	}
}

void URPGItemDiscardScreenWidget::OnValueChanged_SliderDiscardAmount(float InValue)
{
	AmountToDiscard = UKismetMathLibrary::FTrunc(UKismetMathLibrary::MapRangeClamped(InValue, 0.f, 1.f, 1.f, (float)MaxAmontOfItemInInventory));

	TextBlock_DiscardAmount->SetText(FText::FromString("x " + FString::FromInt(AmountToDiscard)));
}

void URPGItemDiscardScreenWidget::UpdateWindowInfo_Implementation(FName& InItemName, FText& InItemDisplayName, int32 InItemAmount)
{
	ItemToDiscard = InItemName;
	
	TextBlock_Info->SetText(FText::FromString("Discard " + InItemDisplayName.ToString()));
	
	MaxAmontOfItemInInventory = InItemAmount;

	Slider_DiscardAmount->SetValue(0.f);

	AmountToDiscard = 1;

	TextBlock_DiscardAmount->SetText(FText::FromString("x " + FString::FromInt(AmountToDiscard)));
}