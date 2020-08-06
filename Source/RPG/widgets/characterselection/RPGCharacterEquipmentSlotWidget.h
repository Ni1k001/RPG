// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "RPG/enums/RPGItemTypeEnum.h"

#include "RPG/structs/RPGBaseItemStruct.h"

#include "RPGCharacterEquipmentSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URPGCharacterEquipmentSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	void NativePreConstruct() override;

	UPROPERTY()
		ItemTypeEnum AssignedItemType;

	UPROPERTY()
		int32 SlotSize;

	UPROPERTY()
		class URPGCharacterSelectScreenWidget* CharacterSelectionScreenReference;

	UPROPERTY()
		class URPGInventoryManagerComponent* InventoryManagerReference;

	UPROPERTY()
		bool bIsDoublePressed;

public:
	UPROPERTY(meta = (BindWidget))
		class UScaleBox* ScaleBox_SlotSize;

	UPROPERTY(meta = (BindWidget))
		class UButton* Button_ChangeEquipment;

	UPROPERTY(meta = (BindWidget))
		class UImage* Image_ItemIcon;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_ItemName;

	UFUNCTION()
		ItemTypeEnum GetAssignedItemType();

	UFUNCTION()
		void SetAssignedItemType(ItemTypeEnum InAssignedItemType);

	UFUNCTION()
		int32 GetSlotSize();

	UFUNCTION()
		void SetSlotSize(int32 InSlotSize);

	UFUNCTION()
		class URPGCharacterSelectScreenWidget* GetCharacterSelectionScreenReference();

	UFUNCTION()
		void SetCharacterSelectionScreenReference(class URPGCharacterSelectScreenWidget* InCharacterSelectionScreenReference);

	UFUNCTION()
		class URPGInventoryManagerComponent* GetInventoryManagerReference();

	UFUNCTION()
		void SetInventoryManagerReference(class URPGInventoryManagerComponent* InInventoryManagerReference);

	UFUNCTION()
		bool GetBIsDoublePressed();

	UFUNCTION()
		void SetBIsDoublePressed(bool InBIsDoublePressed);

	UFUNCTION()
		void OnPressed_ButtonChangeEquipment();

	UFUNCTION()
		void UpdateSlotInfo(FBaseItemStruct InItem);
};
