// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGCharacterSelectionSlotWidget.h"
#include "UMG/Public/Components/Button.h"
#include "UMG/Public/Components/Image.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TimerManager.h"

#include "RPG/components/RPGCharactersManagerComponent.h"

void URPGCharacterSelectionSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!Button_CharacterSlot->OnClicked.IsBound())
		Button_CharacterSlot->OnClicked.AddDynamic(this, &URPGCharacterSelectionSlotWidget::OnPressed_ButtonCharacterSlot);
}

bool URPGCharacterSelectionSlotWidget::GetBIsDoublePressed()
{
	return bIsDoublePressed;
}

void URPGCharacterSelectionSlotWidget::SetBIsDoublePressed(bool InBIsDoublePressed)
{
	bIsDoublePressed = InBIsDoublePressed;
}

URPGCharactersManagerComponent* URPGCharacterSelectionSlotWidget::GetCharactersManagerReference()
{
	return CharactersManagerReference;
}

void URPGCharacterSelectionSlotWidget::SetCharactersManagerReference(URPGCharactersManagerComponent* InCharactersManagerReference)
{
	CharactersManagerReference = InCharactersManagerReference;
}

FName URPGCharacterSelectionSlotWidget::GetCharacterName()
{
	return CharacterName;
}

void URPGCharacterSelectionSlotWidget::SetCharacterName(FName InCharacterName)
{
	CharacterName = InCharacterName;
}

void URPGCharacterSelectionSlotWidget::UpdateSlotData(FName& InName, bool bIsCharacterAssigned/*, image*/)
{
	CharacterName = InName;
	
	if (bIsCharacterAssigned)
		SetVisibility(ESlateVisibility::Visible);
	else
		SetVisibility(ESlateVisibility::Collapsed);

	//Image_CharacterIcon->SetBrushFromTexture();
}

void URPGCharacterSelectionSlotWidget::OnPressed_ButtonCharacterSlot()
{
	if (bIsDoublePressed)
	{
		if (IsValid(CharactersManagerReference))
		{
			bool bSuccess;
			int32 Index;

			CharactersManagerReference->CheckIfCharacterIsInParty(CharacterName, bSuccess, Index);

			if (bSuccess)
				CharactersManagerReference->RemoveCharacterFromParty(CharacterName);
			else
				CharactersManagerReference->AddCharacterToParty(CharacterName);
			
			CharactersManagerReference->RefreshCharacterSelectionSlots();
		}
	}
	else
	{
		if (IsValid(CharactersManagerReference))
		{
			CharactersManagerReference->SetSelectedCharacter(CharacterName);
			CharactersManagerReference->RefreshSelectedCharacterData();

			//Gamepad
		}

		bIsDoublePressed = true;

		FTimerDelegate TimerDelegate;
		FTimerHandle TimerHandle;
		bool TimerVar = false;
		TimerDelegate.BindUFunction(this, FName("SetBIsDoublePressed"), TimerVar);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 1.f, false, 0.25f);
	}
}