// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGCharacterActionsSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URPGCharacterActionsSlotWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	void NativeConstruct() override;

	UPROPERTY()
		bool bIsDoublePressed;

	UPROPERTY()
		class URPGCharactersManagerComponent* CharacterManagerReference;

	UPROPERTY()
		FName AssignedCharacterName;

public:
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_CharacterActionsSlot;

	UPROPERTY(meta = (BindWidget))
		class UImage* Image_Icon;

	UFUNCTION()
		bool GetBIsDoublePressed();

	UFUNCTION()
		void SetBIsDoublePressed(bool InBIsDoublePressed);

	UFUNCTION()
		class URPGCharactersManagerComponent* GetCharacterManagerReference();

	UFUNCTION()
		void SetCharacterManagerReference(class URPGCharactersManagerComponent* InCharacterManagerReference);

	UFUNCTION()
		FName GetAssignedCharacterName();

	UFUNCTION()
		void SetAssignedCharacterName(FName InAssignedCharacterName);

	UFUNCTION()
		void OnPressed_ButtonCharacterActionsSlot();

	UFUNCTION()
		void UpdateSlotData(FName& InName, bool InBIsCharacterAssigned, class UTexture2D* InIcon);
};
