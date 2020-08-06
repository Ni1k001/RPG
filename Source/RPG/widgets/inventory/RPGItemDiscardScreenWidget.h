// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGItemDiscardScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URPGItemDiscardScreenWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void NativeConstruct() override;

    UPROPERTY(BlueprintReadWrite)
        class URPGInventoryManagerComponent* InventoryManagerReference;

    UPROPERTY(BlueprintReadWrite)
        FName ItemToDiscard;

    UPROPERTY(BlueprintReadWrite)
        int32 MaxAmontOfItemInInventory;

    UPROPERTY(BlueprintReadWrite)
        int32 AmountToDiscard;

    UPROPERTY(meta = (BindWidget))
        class UTextBlock* TextBlock_Info;

    UPROPERTY(meta = (BindWidget))
        class UTextBlock* TextBlock_DiscardAmount;

    UPROPERTY(meta = (BindWidget))
        class USlider* Slider_DiscardAmount;

    UPROPERTY(meta = (BindWidget))
        class UButton* Button_Cancel;

    UPROPERTY(meta = (BindWidget))
        class UImage* Image_Cancel;

    UPROPERTY(meta = (BindWidget))
        class UButton* Button_Discard;

    UPROPERTY(meta = (BindWidget))
        class UImage* Image_Discard;

    UFUNCTION()
        void OnPressed_ButtonCancel();

    UFUNCTION()
        void OnPressed_ButtonDiscard();

    UFUNCTION()
        void OnValueChanged_SliderDiscardAmount(float InValue);

    UFUNCTION(BlueprintNativeEvent)
        void UpdateWindowInfo(FName& InItemName, FText& InItemDisplayName, int32 InItemAmount);
};
