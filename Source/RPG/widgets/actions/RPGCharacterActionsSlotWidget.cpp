// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGCharacterActionsSlotWidget.h"
#include "UMG/Public/Components/Button.h"
#include "UMG/Public/Components/Image.h"
#include "Engine/Texture2D.h"

#include "RPG/components/RPGCharactersManagerComponent.h"

void URPGCharacterActionsSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!Button_CharacterActionsSlot->OnClicked.IsBound())
		Button_CharacterActionsSlot->OnClicked.AddDynamic(this, &URPGCharacterActionsSlotWidget::OnPressed_ButtonCharacterActionsSlot);
}

bool URPGCharacterActionsSlotWidget::GetBIsDoublePressed()
{
	return bIsDoublePressed;
}

void URPGCharacterActionsSlotWidget::SetBIsDoublePressed(bool InBIsDoublePressed)
{
	bIsDoublePressed = InBIsDoublePressed;
}

class URPGCharactersManagerComponent* URPGCharacterActionsSlotWidget::GetCharacterManagerReference()
{
	return CharacterManagerReference;
}

void URPGCharacterActionsSlotWidget::SetCharacterManagerReference(class URPGCharactersManagerComponent* InCharacterManagerReference)
{
	CharacterManagerReference = InCharacterManagerReference;
}

FName URPGCharacterActionsSlotWidget::GetAssignedCharacterName()
{
	return AssignedCharacterName;
}

void URPGCharacterActionsSlotWidget::SetAssignedCharacterName(FName InAssignedCharacterName)
{
	AssignedCharacterName = InAssignedCharacterName;
}

void URPGCharacterActionsSlotWidget::OnPressed_ButtonCharacterActionsSlot()
{
	if (CharacterManagerReference->IsValidLowLevel())
	{
		CharacterManagerReference->SetSelectedCharacter(AssignedCharacterName);
		CharacterManagerReference->RefreshSelectedCharacterActionsData();

		//Gamepad
	}
}

void URPGCharacterActionsSlotWidget::UpdateSlotData(FName& InName, bool InBIsCharacterAssigned, class UTexture2D* InIcon)
{
	AssignedCharacterName = InName;

	if (InBIsCharacterAssigned)
		SetVisibility(ESlateVisibility::Visible);
	else
		SetVisibility(ESlateVisibility::Collapsed);

	Image_Icon->SetBrushFromTexture(InIcon, false);
}