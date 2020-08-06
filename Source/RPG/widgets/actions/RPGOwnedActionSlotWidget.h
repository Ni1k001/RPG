// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "RPG/structs/RPGActionStruct.h"

#include "RPGOwnedActionSlotWidget.generated.h"

//#include "RPG/components/RPGCharactersManagerComponent.h"

/**
 * 
 */
UCLASS()
class RPG_API URPGOwnedActionSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	void NativeConstruct() override;

	UPROPERTY()
		class URPGCharactersManagerComponent* CharacterManagerReference;

	UPROPERTY()
		FName AssignedAction;

public:
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_ActionSlot;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_ActionName;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_Level;

	UFUNCTION()
		class URPGCharactersManagerComponent* GetCharacterManagerReference();

	UFUNCTION()
		void SetCharacterManagerReference(class URPGCharactersManagerComponent* InCharacterManagerReference);

	UFUNCTION()
		FName GetAssignedAction();

	UFUNCTION()
		void SetAssignedAction(FName InAssignedAction);

	UFUNCTION()
		void OnPressed_ButtonActionSlot();

	UFUNCTION(BlueprintNativeEvent)
		void UpdateActionData(int32 InActionLevel, FActionStruct InActionData);
};
