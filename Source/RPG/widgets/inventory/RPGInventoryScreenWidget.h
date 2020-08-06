// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "RPG/enums/RPGItemRarityEnum.h"
#include "RPG/enums/RPGItemTypeEnum.h"

#include "RPGInventoryScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URPGInventoryScreenWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite)
		class UButton* HighlightInventoryButton;

	UPROPERTY(BlueprintReadWrite)
		class URPGInventoryManagerComponent* InventoryManagerReference;

	UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* WidgetSwitcher_UseItem;

	UPROPERTY(meta = (BindWidget))
		class UVerticalBox* Container_Inventory;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_Question;

	UPROPERTY(meta = (BindWidget))
		class UButton* Button_CloseItemUse;

	UPROPERTY(meta = (BindWidget))
		class UVerticalBox* Container_UseItemCharacterSlots;

	UPROPERTY(meta = (BindWidget))
		class UHorizontalBox* HorizontalBox_GamepadHints;

	UPROPERTY(meta = (BindWidget))
		class UButton* Button_0;

	UPROPERTY(meta = (BindWidget))
		class UImage* Image_0;

	UPROPERTY(meta = (BindWidget))
		class UButton* Button_1;

	UPROPERTY(meta = (BindWidget))
		class UImage* Image_1;

	UPROPERTY(meta = (BindWidget))
		class UVerticalBox* Container_ItemDetails;
	
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_ItemName;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_ItemRarity;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_ItemType;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_ItemDescription;

	UPROPERTY(meta = (BindWidget))
		class UHorizontalBox* HorizontalBox_ItemButtons;

	UPROPERTY(meta = (BindWidget))
		class UButton* Button_Use;

	UPROPERTY(meta = (BindWidget))
		class UImage* Image_Use;

	UPROPERTY(meta = (BindWidget))
		class UButton* Button_Discard;

	UPROPERTY(meta = (BindWidget))
		class UImage* Image_Discard;

	UFUNCTION()
		void OnPressed_ButtonDiscard();

	UFUNCTION()
		void OnPressed_ButtonUse();

	UFUNCTION()
		void OnPressed_ButtonCloseItemUse();

	UFUNCTION(BlueprintNativeEvent)
		void UpdateItemDetails(FText& InItemName, ItemTypeEnum InItemType, ItemRarityEnum InItemRarity, FText& InItemDescription);

	UFUNCTION(BlueprintNativeEvent)
		void HighlightNewInventoryButton(class UButton* InButton);

	UFUNCTION(BlueprintNativeEvent)
		void UnhighlightInventoryButton();
};
