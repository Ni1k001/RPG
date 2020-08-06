// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "RPG/structs/RPGBaseItemStruct.h"

#include "RPGInventorySlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URPGInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    void NativeConstruct() override;

    UPROPERTY(BlueprintReadWrite)
        class URPGInventoryManagerComponent* InventoryManagerReference;

    UPROPERTY(meta = (BindWidget))
        class UButton* Button_InventorySlot;

    UPROPERTY(meta = (BindWidget))
        class UImage* Image_ItemIcon;

    UPROPERTY(meta = (BindWidget))
        class UTextBlock* TextBlock_ItemName;

    UPROPERTY(meta = (BindWidget))
        class UTextBlock* TextBlock_Amount;

    UFUNCTION()
        void OnPressed();

    UFUNCTION(BlueprintNativeEvent)
        void UpdateItemData(int32 InCurrentStackAmount, FBaseItemStruct InItem);
};
