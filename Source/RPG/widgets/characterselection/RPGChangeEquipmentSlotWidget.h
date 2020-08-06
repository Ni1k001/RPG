// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "RPG/structs/RPGBaseItemStruct.h"

#include "RPGChangeEquipmentSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URPGChangeEquipmentSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	void NativeConstruct() override;

	UPROPERTY()
		FName AssignedItemName;

	UPROPERTY()
		class URPGInventoryManagerComponent* InventoryManagerReference;

	UPROPERTY()
		class URPGCharacterSelectScreenWidget* CharacterSelectionScreenReference;

	UPROPERTY()
		bool bIsDoublePressed;
public:
	UPROPERTY(meta = (BindWidget))
		class UScaleBox* ScaleBox_SlotSize;

	UPROPERTY(meta = (BindWidget))
		class UButton* Button_ChangeEquipment;

	UPROPERTY(meta = (BindWidget))
		class UImage* Image_DefaultIcon;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_ItemName;

	UFUNCTION()
		FName GetAssignedItemName();

	UFUNCTION()
		void SetAssignedItemName(FName InAssignedItemName);

	UFUNCTION()
		class URPGInventoryManagerComponent* GetInventoryManagerReference();

	UFUNCTION()
		void SetInventoryManagerReference(class URPGInventoryManagerComponent* InInventoryManagerReference);

	UFUNCTION()
		class URPGCharacterSelectScreenWidget* GetCharacterSelectionScreenReference();

	UFUNCTION()
		void SetCharacterSelectionScreenReference(class URPGCharacterSelectScreenWidget* InCharacterSelectionScreenReference);

	UFUNCTION()
		bool GetBIsDoublePressed();

	UFUNCTION()
		void SetBIsDoublePressed(bool InBIsDoublePressed);

	UFUNCTION()
		void OnPressed_ButtonChangeEquipment();

	UFUNCTION()
		void UpdateSlotInfo(FBaseItemStruct InItem);
};
