// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGOwnedActionSlotWidget.h"
#include "UMG/Public/Components/Button.h"
#include "UMG/Public/Components/ScrollBox.h"
#include "UMG/Public/Components/TextBlock.h"

#include "RPG/components/RPGCharactersManagerComponent.h"

void URPGOwnedActionSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!Button_ActionSlot->OnClicked.IsBound())
		Button_ActionSlot->OnClicked.AddDynamic(this, &URPGOwnedActionSlotWidget::OnPressed_ButtonActionSlot);
}

URPGCharactersManagerComponent* URPGOwnedActionSlotWidget::GetCharacterManagerReference()
{
	return CharacterManagerReference;
}

void URPGOwnedActionSlotWidget::SetCharacterManagerReference(URPGCharactersManagerComponent* InCharacterManagerReference)
{
	CharacterManagerReference = InCharacterManagerReference;
}

FName URPGOwnedActionSlotWidget::GetAssignedAction()
{
	return AssignedAction;
}

void URPGOwnedActionSlotWidget::SetAssignedAction(FName InAssignedAction)
{
	AssignedAction = InAssignedAction;
}

void URPGOwnedActionSlotWidget::OnPressed_ButtonActionSlot()
{
	if (CharacterManagerReference->IsValidLowLevel())
	{
		CharacterManagerReference->SetSelectedAction(AssignedAction);
		CharacterManagerReference->RefreshSelectedActionData(AssignedAction);
		//CharacterManagerReference->

		Cast<UScrollBox>(this->GetParent()->GetParent())->ScrollWidgetIntoView(this, true, EDescendantScrollDestination::Center);
	}
}

void URPGOwnedActionSlotWidget::UpdateActionData_Implementation(int32 InActionLevel, FActionStruct InActionData)
{
	TextBlock_Level->SetText(FText::FromString("Lv. " + FString::FromInt(InActionLevel)));

	AssignedAction = InActionData.Name;

	TextBlock_ActionName->SetText(InActionData.DisplayName);

	SetVisibility(ESlateVisibility::Visible);
}