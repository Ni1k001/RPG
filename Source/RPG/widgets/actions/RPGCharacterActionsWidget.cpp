// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGCharacterActionsWidget.h"
#include "UMG/Public/Components/Button.h"
#include "UMG/Public/Components/HorizontalBox.h"
#include "UMG/Public/Components/Image.h"
#include "UMG/Public/Components/VerticalBox.h"

#include "RPG/components/RPGCharactersManagerComponent.h"

void URPGCharacterActionsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!Button_Upgrade->OnClicked.IsBound())
		Button_Upgrade->OnClicked.AddDynamic(this, &URPGCharacterActionsWidget::OnPressed_ButtonUpgrade);

	//Gamepad
}

class UButton* URPGCharacterActionsWidget::GetHighlightCharacterActionButtonReference()
{
	return HighlightCharacterActionButtonReference;
}

void URPGCharacterActionsWidget::SetHighlightCharacterActionButtonReference(class UButton* InHighlightCharacterActionButtonReference)
{
	HighlightCharacterActionButtonReference = InHighlightCharacterActionButtonReference;
}

class UButton* URPGCharacterActionsWidget::GetHighlightOwnedActionButtonReference()
{
	return HighlightOwnedActionButtonReference;
}

void URPGCharacterActionsWidget::SetHighlightOwnedActionButtonReference(class UButton* InHighlightOwnedActionButtonReference)
{
	HighlightOwnedActionButtonReference = InHighlightOwnedActionButtonReference;
}

void URPGCharacterActionsWidget::HighlightNewSelectedCharacterSlot(class UButton* InButton)
{
	UnhighlightSelectedCharacterSlot();

	HighlightCharacterActionButtonReference = InButton;
	HighlightCharacterActionButtonReference->SetBackgroundColor(FLinearColor(FColor::FromHex("#FF7F0066")));
}

void URPGCharacterActionsWidget::UnhighlightSelectedCharacterSlot()
{
	if (HighlightCharacterActionButtonReference->IsValidLowLevel())
		HighlightCharacterActionButtonReference->SetBackgroundColor(FLinearColor(FColor::FromHex("#FFFFFF66")));
}

void URPGCharacterActionsWidget::HighlightNewOwnedActionSlot(class UButton* InButton)
{
	UnhighlightOwnedActionSlot();

	HighlightOwnedActionButtonReference = InButton;
	HighlightOwnedActionButtonReference->SetBackgroundColor(FLinearColor(FColor::FromHex("#FFFFFF66")));
}

void URPGCharacterActionsWidget::UnhighlightOwnedActionSlot()
{
	if (HighlightOwnedActionButtonReference->IsValidLowLevel())
		HighlightOwnedActionButtonReference->SetBackgroundColor(FLinearColor(FColor::FromHex("#FFFFFF66")));
}

void URPGCharacterActionsWidget::EnableUpgradeButton(bool InBIsEnabled)
{
	Button_Upgrade->SetIsEnabled(InBIsEnabled);
}

void URPGCharacterActionsWidget::OnPressed_ButtonUpgrade()
{
	URPGCharactersManagerComponent* CMC = Cast<URPGCharactersManagerComponent>(GetWorld()->GetFirstPlayerController()->GetComponentByClass(URPGCharactersManagerComponent::StaticClass()));

	CMC->UpgradeAction(CMC->GetSelectedCharacter(), CMC->GetSelectedAction());
}