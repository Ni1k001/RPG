// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGBattleCharacterSlotWidget.h"
#include "UMG/Public/Components/ProgressBar.h"
#include "UMG/Public/Components/TextBlock.h"
#include "UMG/Public/Components/Border.h"

#include "RPG/components/RPGBattleCharacterStatsComponent.h"

void URPGBattleCharacterSlotWidget::UpdateHealthValue_Implementation(float InCurrent, float InMax)
{
	TextBlock_HPValue->SetText(FText::FromString(FString::SanitizeFloat(InCurrent) + "/" + FString::SanitizeFloat(InMax)));
	ProgressBar_HP->SetPercent(InCurrent / InMax);
}

void URPGBattleCharacterSlotWidget::UpdateManaValue_Implementation(float InCurrent, float InMax)
{
	TextBlock_MPValue->SetText(FText::FromString(FString::SanitizeFloat(InCurrent) + "/" + FString::SanitizeFloat(InMax)));
	ProgressBar_MP->SetPercent(InCurrent / InMax);
}

void URPGBattleCharacterSlotWidget::UpdateInitiativeValue_Implementation(float InCurrent, float InMax)
{
	ProgressBar_Initiative->SetPercent(InCurrent / InMax);
}

void URPGBattleCharacterSlotWidget::UpdateCharacterDisplayName_Implementation(const FText& InCharacterDisplayName)
{
	TextBlock_CharacterName->SetText(InCharacterDisplayName);
}

void URPGBattleCharacterSlotWidget::HighlightSlot_Implementation()
{
	Border_Highlight->SetBrushColor(FLinearColor::FromSRGBColor(FColor::FromHex("#FFDFDF66")));
}

void URPGBattleCharacterSlotWidget::UnhighlightSlot_Implementation()
{
	Border_Highlight->SetBrushColor(FLinearColor::FromSRGBColor(FColor::FromHex("#19191933")));
}

void URPGBattleCharacterSlotWidget::DarkenSlotOnDeath_Implementation()
{
	Border_Highlight->SetContentColorAndOpacity(FLinearColor::FromSRGBColor(FColor::FromHex("#0C0C0CFF")));
	ProgressBar_Initiative->SetPercent(0.f);
}

void URPGBattleCharacterSlotWidget::RestoreSlotOnResurrection_Implementation()
{
	Border_Highlight->SetContentColorAndOpacity(FLinearColor::FromSRGBColor(FColor::FromHex("#FFFFFFFF")));
	ProgressBar_Initiative->SetPercent(0.f);
}