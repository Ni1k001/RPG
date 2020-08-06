// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGCharacterSelectScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URPGCharacterSelectScreenWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	void NativePreConstruct() override;
	void NativeConstruct() override;

	UPROPERTY()
		TArray<class URPGStatSlotWidget*> StatSlotsReference;

	UPROPERTY()
		TArray<class URPGCharacterEquipmentSlotWidget*> EquipmentSlotsReference;
	
	UPROPERTY()
		class UButton* HighlightEquipmentChangeButtonReference;

	UPROPERTY()
		class UButton* HighlightCharacterSelectionButtonReference;

	UPROPERTY()
		class UButton* HighlightSelectEquipmentButtonReference;

public:
	UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* WidgetSwitcher_Selection;

	UPROPERTY(meta = (BindWidget))
		class UWrapBox* Container_CurrentTeam;

	UPROPERTY(meta = (BindWidget))
		class UWrapBox* Container_OtherCharacters;

	UPROPERTY(meta = (BindWidget))
		class UButton* Button_Close;

	UPROPERTY(meta = (BindWidget))
		class UVerticalBox* Container_EquipmentChange;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_CharacterName;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_Level;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_Exp;

	UPROPERTY(meta = (BindWidget))
		class URPGStatSlotWidget* StatSlot_HP;

	UPROPERTY(meta = (BindWidget))
		class URPGStatSlotWidget* StatSlot_MP;

	UPROPERTY(meta = (BindWidget))
		class URPGStatSlotWidget* StatSlot_Vitality;

	UPROPERTY(meta = (BindWidget))
		class URPGStatSlotWidget* StatSlot_Magic;

	UPROPERTY(meta = (BindWidget))
		class URPGStatSlotWidget* StatSlot_Spirit;

	UPROPERTY(meta = (BindWidget))
		class URPGStatSlotWidget* StatSlot_Strength;

	UPROPERTY(meta = (BindWidget))
		class URPGStatSlotWidget* StatSlot_Dexterity;

	UPROPERTY(meta = (BindWidget))
		class URPGStatSlotWidget* StatSlot_Luck;

	UPROPERTY(meta = (BindWidget))
		class URPGStatSlotWidget* StatSlot_Initiative;

	UPROPERTY(meta = (BindWidget))
		class UVerticalBox* Container_CharacterEquipment;

	UPROPERTY(meta = (BindWidget))
		class URPGCharacterEquipmentSlotWidget* CharacterEquipmentSlot_Weapon;

	UPROPERTY(meta = (BindWidget))
		class URPGCharacterEquipmentSlotWidget* CharacterEquipmentSlot_Armor;

	UPROPERTY(meta = (BindWidget))
		class URPGCharacterEquipmentSlotWidget* CharacterEquipmentSlot_Accessory;

	UFUNCTION()
		TArray<class URPGStatSlotWidget*> GetStatSlotsReference();

	UFUNCTION()
		void SetStatSlotsReference(TArray<class URPGStatSlotWidget*> InStatSlotsReference);

	UFUNCTION()
		TArray<class URPGCharacterEquipmentSlotWidget*> GetEquipmentSlotsReference();

	UFUNCTION()
		void SetEquipmentSlotsReference(TArray<class URPGCharacterEquipmentSlotWidget*> InEquipmentSlotsReference);

/*	UFUNCTION()
		class UButton* GetHighlightEquipmentChangeButtonReference();

	UFUNCTION()
		void SetHighlightEquipmentChangeButtonReference(class UButton* InHighlightEquipmentChangeButtonReference);

	UFUNCTION()
		class UButton* GetHighlightCharacterSelectionButtonReference();

	UFUNCTION()
		void SetHighlightCharacterSelectionButtonReference(class UButton* InHighlightCharacterSelectionButtonReference);

	UFUNCTION()
		class UButton* GetHighlightSelectEquipmentButtonReference();

	UFUNCTION()
		void SetHighlightSelectEquipmentButtonReference(class UButton* InHighlightSelectEquipmentButtonReference);*/
	
	UFUNCTION()
		void OnPressed_ButtonClose();

	UFUNCTION()
		void HighlightNewEquipmentChangeButton(class UButton* InButton);

	UFUNCTION()
		void UnhighlighteEquipmentChangeButton();

	UFUNCTION()
		void HighlightNewCharacterSelectionButton(class UButton* InButton);

	UFUNCTION()
		void UnhighlightCharacterSelectionButton();

	UFUNCTION()
		void HighlightNewSelectEquipmentButton(class UButton* InButton);

	UFUNCTION()
		void UnhighlightSelectEquipmentButton();
};
