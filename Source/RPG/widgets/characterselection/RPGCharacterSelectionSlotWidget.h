// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGCharacterSelectionSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URPGCharacterSelectionSlotWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	void NativeConstruct() override;

	UPROPERTY()
		bool bIsDoublePressed;

	UPROPERTY()
		URPGCharactersManagerComponent* CharactersManagerReference;

	UPROPERTY()
		FName CharacterName;

public:
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_CharacterSlot;

	UPROPERTY(meta = (BindWidget))
		class UImage* Image_CharacterIcon;

	UFUNCTION()
		bool GetBIsDoublePressed();

	UFUNCTION()
		void SetBIsDoublePressed(bool InBIsDoublePressed);

	UFUNCTION()
		class URPGCharactersManagerComponent* GetCharactersManagerReference();

	UFUNCTION()
		void SetCharactersManagerReference(URPGCharactersManagerComponent* InCharactersManagerReference);

	UFUNCTION()
		FName GetCharacterName();

	UFUNCTION()
		void SetCharacterName(FName InCharacterName);

	UFUNCTION()
		void UpdateSlotData(FName& InName, bool bIsCharacterAssigned/*, image*/);

	UFUNCTION()
		void OnPressed_ButtonCharacterSlot();
};
