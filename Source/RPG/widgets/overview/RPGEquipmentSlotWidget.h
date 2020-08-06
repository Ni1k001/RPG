// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "RPG/enums/RPGItemTypeEnum.h"

#include "RPG/structs/RPGBaseItemStruct.h"

#include "RPGEquipmentSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URPGEquipmentSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
	void NativePreConstruct();

public:
	UPROPERTY(BlueprintReadWrite)
		ItemTypeEnum AssignedItemType;

	UPROPERTY(BlueprintReadWrite)
		int32 SlotSize;

	UPROPERTY(meta = (BindWidget))
		class UScaleBox* ScaleBox_SlotSize;

	UPROPERTY(meta = (BindWidget))
		class UImage* Image_Icon;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_ItemName;

	UFUNCTION(BlueprintNativeEvent)
		void UpdateSlotInfo(FBaseItemStruct Item);
};
