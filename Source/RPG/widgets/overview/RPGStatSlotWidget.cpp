// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGStatSlotWidget.h"

#include "UMG/Public/Components/HorizontalBox.h"
#include "UMG/Public/Components/Image.h"
#include "UMG/Public/Components/TextBlock.h"

#include "RPG/RPGCustomFunctionLibrary.h"

void URPGStatSlotWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	TextBlock_StatName->SetText(URPGCustomFunctionLibrary::StatTypeToText(AssignedStatType));

	TextBlock_StatName->Font.Size = FontSize;
	TextBlock_StatValue->Font.Size = FontSize;
	TextBlock_NewValue->Font.Size = FontSize;

	if (!bIsComparisonEnabled)
		HorizontalBox_Change->SetVisibility(ESlateVisibility::Collapsed);
	else
		HorizontalBox_Change->SetVisibility(ESlateVisibility::Hidden);
}

void URPGStatSlotWidget::SetComparisonPartToHigher_Implementation(float InValue)
{
	HorizontalBox_Change->SetVisibility(ESlateVisibility::HitTestInvisible);

	//Image_Arrow->SetBrushFromTexture(, false);

	Image_Arrow->SetVisibility(ESlateVisibility::HitTestInvisible);

	TextBlock_NewValue->SetText(FText::FromString(FString::SanitizeFloat(InValue)));
	TextBlock_NewValue->SetColorAndOpacity(FLinearColor::FromSRGBColor(FColor::FromHex("#00FF00FF")));
}

void URPGStatSlotWidget::SetComparisonPartToLower_Implementation(float InValue)
{
	HorizontalBox_Change->SetVisibility(ESlateVisibility::HitTestInvisible);

	//Image_Arrow->SetBrushFromTexture(, false);

	Image_Arrow->SetVisibility(ESlateVisibility::HitTestInvisible);

	TextBlock_NewValue->SetText(FText::FromString(FString::SanitizeFloat(InValue)));
	TextBlock_NewValue->SetColorAndOpacity(FLinearColor::FromSRGBColor(FColor::FromHex("#FF0000FF")));
}

void URPGStatSlotWidget::SetComparisonPartToEqual_Implementation(float InValue)
{
	HorizontalBox_Change->SetVisibility(ESlateVisibility::HitTestInvisible);

	Image_Arrow->SetVisibility(ESlateVisibility::Collapsed);

	TextBlock_NewValue->SetText(FText::FromString(FString::SanitizeFloat(InValue)));
	TextBlock_NewValue->SetColorAndOpacity(FLinearColor::FromSRGBColor(FColor::FromHex("#FFFFFFFF")));
}