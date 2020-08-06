// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "RPG/enums/RPGItemTypeEnum.h"

#include "RPG/structs/RPGBaseItemStruct.h"
#include "RPG/structs/RPGItemDataStruct.h"

#include "RPGInventoryManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API URPGInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URPGInventoryManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
		int32 InventorySlotsAmount;

	UPROPERTY()
		bool bIsMultipleStacksAllowed;

	UPROPERTY()
		TArray<class URPGInventorySlotWidget*> InventorySlotsReference;

	UPROPERTY()
		class URPGInventoryScreenWidget* InventoryScreenReference;

	UPROPERTY()
		class URPGItemDiscardScreenWidget* DiscardItemScreenReference;

	UPROPERTY()
		int32 SelectedItemSlot;

//	UPROPERTY()
//		ChangeEquipmentSlotReference;

//	UPROPERTY()
//		UseItemOnCharacterSlotsReference;

	UPROPERTY()
		FName ItemToUse;

//	UPROPERTY()
//		VendorWindow;

//	UPROPERTY()
//		VendroItemSlots;

	UPROPERTY()
		TSet<FName> VendorItems;

	UPROPERTY()
		int32 SelectedVendorSlot;

	UPROPERTY()
		class URPGGameInstance* GI;

public:
	UFUNCTION()
		int32 GetInventorySlotsAmount();

	UFUNCTION()
		void SetInventorySlotsAmount(int32 InInventorySlotsAmount);

	UFUNCTION()
		bool GetBIsMultipleStacksAllowed();

	UFUNCTION()
		void SetBIsMultipleStacksAllowed(bool InBIsMultipleStacksAllowed);

	UFUNCTION()
		TArray<class URPGInventorySlotWidget*> GetInventorySlotsReference();

	UFUNCTION()
		void SetInventorySlotsReference(TArray<class URPGInventorySlotWidget*> InInventorySlot);

	UFUNCTION()
		class URPGInventoryScreenWidget* GetInventoryScreenReference();

	UFUNCTION()
		void SetInventoryScreenReference(class URPGInventoryScreenWidget* InInventoryScreenReference);

	UFUNCTION()
		class URPGItemDiscardScreenWidget* GetDiscardItemScreenReference();

	UFUNCTION()
		void SetDiscardItemScreenReference(class URPGItemDiscardScreenWidget* InDiscardItemScreenReference);

	UFUNCTION()
		int32 GetSelectedItemSlot();

	UFUNCTION()
		void SetSelectedItemSlot(int32 InSelectedItemSlot);

//	UFUNCTION()
//		GetChangeEquipmentSlotReference();

//	UFUNCTION()
//		SetChangeEquipmentSlotReference();

//	UFUNCTION()
//		GetUseItemOnCharacterSlotsReference();

//	UFUNCTION()
//		SetUseItemOnCharacterSlotsReference();

	UFUNCTION()
		FName GetItemToUse();

	UFUNCTION()
		void SetItemToUse(FName InItemToUse);

//	UFUNCTION()
//		GetVendorWindow();

//	UFUNCTION()
//		SetVendorWindow();

//	UFUNCTION()
//		GetVendroItemSlots();

//	UFUNCTION()
//		SetVendroItemSlots();

	UFUNCTION()
		TSet<FName> GetVendorItems();

	UFUNCTION()
		void SetVendorItems(TSet<FName> InVendorItems);

	UFUNCTION()
		int32 GetSelectedVendorSlot();

	UFUNCTION()
		void SetSelectedVendorSlot(int32 InSelectedVendorSlot);

	/*				INITIALIZATION				*/
	UFUNCTION()
		void CreateReferenceToInventoryWindow();

	UFUNCTION()
		void CreateReferenceToVendorWindow();

	/*				CHECKERS					*/
	UFUNCTION()
		void CheckIfItemIsNotFullyStackedInInventory(FName InItemName, bool& OutBSuccess, int32& OutIndex);

	UFUNCTION()
		bool CheckIfThereIsFreeSlotInInventory();

	UFUNCTION()
		void CheckIfItemIsInInventory(FName InItemName, bool& OutBSuccess, bool& OutBIsItemFullyStacked, int32& OutIndex);

	UFUNCTION()
		bool CheckIfThereIsAmountOfItemInInventory(FName InItemName, int32 InAmount);

	UFUNCTION()
		bool CheckIfCanUnequipItemToInventory(FName InItemName);

	UFUNCTION()
		int32 CheckAmountOfItemsInInventory(FName InItemName);

	UFUNCTION()
		bool CheckIfItemCanBeBought(FName InItemName);

	UFUNCTION()
		bool CheckIfItemCanBeSold(FName InItemName);

	/*				INVENTORY MANAGER			*/
	UFUNCTION()
		void AddItemToInventory(FName InItemName, int32 InAmount);

	UFUNCTION()
		void RemoveItemFromInventory(FName InItemName, int32 InAmount);

	UFUNCTION()
		void RefreshAllInventorySlots();

	UFUNCTION()
		class URPGInventorySlotWidget* GetProperInventorySlotWidget(int32 InIndex);

	UFUNCTION()
		void RefreshInventorySlot(int32 InIndex);

	UFUNCTION()
		void ReleaseInventorySlot(int32 InIndex);

	UFUNCTION()
		void RefreshItemDetails();

	UFUNCTION()
		void ShowDiscardWindow();

	UFUNCTION()
		void RefreshInventorySlotAfterDiscarding(int32 InIndex);

	/*				EQUIPMENT CHANGING			*/
	UFUNCTION()
		TArray<FItemDataStruct> GetAllEqupableItems(ItemTypeEnum InItemType);

	UFUNCTION()
		void EquipItem(FName InItemName);

	UFUNCTION()
		FBaseItemStruct GetItemStructFromInventory(FName InItemName);

	UFUNCTION()
		void CalculateStatsComparisonOnEquip(FName InItemName);

	UFUNCTION()
		void UnequipItem(ItemTypeEnum InItemType);

	UFUNCTION()
		void ShowAllEquipableItems(ItemTypeEnum InItemType);

//	UFUNCTION()
//		GetProperEquipmentChangeSlot(int32 InIndex);

	/*				USE ITEM					*/
	UFUNCTION()
		void RefreshUseItemOnCharacterSlots();

//	UFUNCTION()
//		GetProperUseItemOnCharacterSlotWidget(int32 InIndex);

	UFUNCTION()
		void SelectItemToUse();

	UFUNCTION()
		void UseItemOnCharacter(FName InItemToUse, FName InCharacterName);

	/*				CURRENCY					*/
	UFUNCTION()
		void RefreshGoldAmount();

	UFUNCTION()
		void ReceiveGold(int32 InGold);

	UFUNCTION()
		void SpendGold(int32 InGold);

	/*				VENDOR MANAGEMENT			*/
	UFUNCTION()
		void ShowItemsToBuy(int32 InSlotToFocus);

//	UFUNCTION()
//		GetProperVendorSlot(int32 InIndex);

	UFUNCTION()
		void RefreshVendorItemDetails(bool InBShowItemFromInventory);

	UFUNCTION()
		void ShowItemsToSell(int32 InSlotToFocus);

	UFUNCTION()
		void BuyItem(FName InItemName);

	UFUNCTION()
		void SellItem(FName InItemName);

	/*				MACRO						*/
	UFUNCTION()
		bool GetIsCharacterAlive(FName InName);
};
