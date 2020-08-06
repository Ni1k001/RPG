// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGCharacterActionsWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URPGCharacterActionsWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	void NativeConstruct() override;

	UPROPERTY()
		class UButton* HighlightCharacterActionButtonReference;

	UPROPERTY()
		class UButton* HighlightOwnedActionButtonReference;

public:
	UPROPERTY(meta = (BindWidget))
		class UHorizontalBox* Container_CurentPartySlots;

	UPROPERTY(meta = (BindWidget))
		class UVerticalBox* Container_Actions;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_CharacterName;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_ActionName;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_Description;

	UPROPERTY(meta = (BindWidget))
		class UButton* Button_Upgrade;

	UPROPERTY(meta = (BindWidget))
		class UImage* Image_ButtonIcon;

	UFUNCTION()
		class UButton* GetHighlightCharacterActionButtonReference();

	UFUNCTION()
		void SetHighlightCharacterActionButtonReference(class UButton* InHighlightCharacterActionButtonReference);

	UFUNCTION()
		class UButton* GetHighlightOwnedActionButtonReference();

	UFUNCTION()
		void SetHighlightOwnedActionButtonReference(class UButton* InHighlightOwnedActionButtonReference);

	UFUNCTION()
		void HighlightNewSelectedCharacterSlot(class UButton* InButton);

	UFUNCTION()
		void UnhighlightSelectedCharacterSlot();

	UFUNCTION()
		void HighlightNewOwnedActionSlot(class UButton* InButton);

	UFUNCTION()
		void UnhighlightOwnedActionSlot();

	UFUNCTION()
		void EnableUpgradeButton(bool InBIsEnabled);

	UFUNCTION()
		void OnPressed_ButtonUpgrade();
};
