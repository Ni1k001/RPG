// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGInventoryManagerComponent.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UMG/Public/Components/VerticalBox.h"
#include "UMG/Public/Components/Button.h"

#include "RPG/RPGGameInstance.h"
#include "RPG/RPGCharacter.h"
#include "RPG/RPGCustomFunctionLibrary.h"
#include "RPG/RPGDataTables.h"

#include "RPG/battle/RPGBattleCharacter.h"

#include "RPG/components/RPGBattleCharacterStatsComponent.h"
#include "RPG/components/RPGCharactersManagerComponent.h"
#include "RPG/components/RPGDynamicCameraManagerComponent.h"
#include "RPG/components/RPGTargetingManagerComponent.h"

#include "RPG/structs/RPGCharacterInfoStruct.h"

#include "RPG/widgets/inventory/RPGInventoryScreenWidget.h"
#include "RPG/widgets/inventory/RPGInventorySlotWidget.h"
#include "RPG/widgets/inventory/RPGItemDiscardScreenWidget.h"

// Sets default values for this component's properties
URPGInventoryManagerComponent::URPGInventoryManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URPGInventoryManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	while (!GI)
	{
		GI = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());
	}
}


// Called every frame
void URPGInventoryManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int32 URPGInventoryManagerComponent::GetInventorySlotsAmount()
{
	return InventorySlotsAmount;
}

void URPGInventoryManagerComponent::SetInventorySlotsAmount(int32 InInventorySlotsAmount)
{
	InventorySlotsAmount = InInventorySlotsAmount;
}

bool URPGInventoryManagerComponent::GetBIsMultipleStacksAllowed()
{
	return bIsMultipleStacksAllowed;
}

void URPGInventoryManagerComponent::SetBIsMultipleStacksAllowed(bool InBIsMultipleStacksAllowed)
{
	bIsMultipleStacksAllowed = InBIsMultipleStacksAllowed;
}

TArray<URPGInventorySlotWidget*> URPGInventoryManagerComponent::GetInventorySlotsReference()
{
	return InventorySlotsReference;
}

void URPGInventoryManagerComponent::SetInventorySlotsReference(TArray<URPGInventorySlotWidget*> InInventorySlotsReference)
{
	InventorySlotsReference = InInventorySlotsReference;
}

URPGInventoryScreenWidget* URPGInventoryManagerComponent::GetInventoryScreenReference()
{
	return InventoryScreenReference;
}

void URPGInventoryManagerComponent::SetInventoryScreenReference(URPGInventoryScreenWidget* InInventoryScreenReference)
{
	InventoryScreenReference = InInventoryScreenReference;
}

URPGItemDiscardScreenWidget* URPGInventoryManagerComponent::GetDiscardItemScreenReference()
{
	return DiscardItemScreenReference;
}

void URPGInventoryManagerComponent::SetDiscardItemScreenReference(URPGItemDiscardScreenWidget* InDiscardItemScreenReference)
{
	DiscardItemScreenReference = InDiscardItemScreenReference;
}

int32 URPGInventoryManagerComponent::GetSelectedItemSlot()
{
	return SelectedItemSlot;
}

void URPGInventoryManagerComponent::SetSelectedItemSlot(int32 InSelectedItemSlot)
{
	SelectedItemSlot = InSelectedItemSlot;
}

// URPGInventoryManagerComponent::GetChangeEquipmentSlotReference();

// URPGInventoryManagerComponent::SetChangeEquipmentSlotReference();

// URPGInventoryManagerComponent::GetUseItemOnCharacterSlotsReference();

// URPGInventoryManagerComponent::SetUseItemOnCharacterSlotsReference();

FName URPGInventoryManagerComponent::GetItemToUse()
{
	return ItemToUse;
}

void URPGInventoryManagerComponent::SetItemToUse(FName InItemToUse)
{
	ItemToUse = InItemToUse;
}

// URPGInventoryManagerComponent::GetVendorWindow();

// URPGInventoryManagerComponent::SetVendorWindow();

// URPGInventoryManagerComponent::GetVendroItemSlots();

// URPGInventoryManagerComponent::SetVendroItemSlots();

TSet<FName> URPGInventoryManagerComponent::GetVendorItems()
{
	return VendorItems;
}

void URPGInventoryManagerComponent::SetVendorItems(TSet<FName> InVendorItems)
{
	VendorItems = InVendorItems;
}

int32 URPGInventoryManagerComponent::GetSelectedVendorSlot()
{
	return SelectedVendorSlot;
}

void URPGInventoryManagerComponent::SetSelectedVendorSlot(int32 InSelectedVendorSlot)
{
	SelectedVendorSlot = InSelectedVendorSlot;
}

/*				INITIALIZATION				*/
void URPGInventoryManagerComponent::CreateReferenceToInventoryWindow() //DONE
{
	TArray<UUserWidget*> FoundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, URPGInventoryScreenWidget::StaticClass(), false);

	if (FoundWidgets.IsValidIndex(0))
	{
		Cast<URPGInventoryScreenWidget>(FoundWidgets[0])->InventoryManagerReference = this;

		InventoryScreenReference = Cast<URPGInventoryScreenWidget>(FoundWidgets[0]);

		RefreshItemDetails();
		RefreshAllInventorySlots();
		RefreshGoldAmount();
	}
}

void URPGInventoryManagerComponent::CreateReferenceToVendorWindow() //TODO
{

}

/*				CHECKERS					*/
void URPGInventoryManagerComponent::CheckIfItemIsNotFullyStackedInInventory(FName InItemName, bool& OutBSuccess, int32& OutIndex) //DONE
{
	//URPGGameInstance* GI = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());

	for (int i = 0; i < GI->GetInventory().Num(); i++)
	{
		if (GI->GetInventory()[i].BaseItemData.ItemName == InItemName)
		{
			if (GI->GetInventory()[i].StackAmount < GI->GetInventory()[i].BaseItemData.MaxStackAmount)
			{
				OutBSuccess = true;
				OutIndex = i;
				return;
			}
		}
	}
}

bool URPGInventoryManagerComponent::CheckIfThereIsFreeSlotInInventory() //DONE
{
	if (InventorySlotsAmount == 0)
		return false;

//	URPGGameInstance* GI = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());

	if (GI->GetInventory().Num() < InventorySlotsAmount)
		return true;

	return false;
}

void URPGInventoryManagerComponent::CheckIfItemIsInInventory(FName InItemName, bool& OutBSuccess, bool& OutBIsItemFullyStacked, int32& OutIndex) //DONE
{
//	URPGGameInstance* GI = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());

	for (int i = 0; i < GI->GetInventory().Num(); i++)
	{
		if (GI->GetInventory()[i].BaseItemData.ItemName == InItemName)
		{
			OutBSuccess = true;
			OutIndex = i;

			if (GI->GetInventory()[i].StackAmount == GI->GetInventory()[i].BaseItemData.MaxStackAmount)
				OutBIsItemFullyStacked = true;
			else
				OutBIsItemFullyStacked = false;

			return;
		}
	}
}

bool URPGInventoryManagerComponent::CheckIfThereIsAmountOfItemInInventory(FName InItemName, int32 InAmount) //DONE
{
//	URPGGameInstance* GI = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());
	
	int32 TotalAmount = 0;

	if (bIsMultipleStacksAllowed)
	{
		for (int i = 0; i < GI->GetInventory().Num(); i++)
		{
			if (GI->GetInventory()[i].BaseItemData.ItemName == InItemName)
				TotalAmount += GI->GetInventory()[i].StackAmount;
		}

		if (TotalAmount >= InAmount)
			return true;
		return false;
	}

	for (int i = 0; i < GI->GetInventory().Num(); i++)
	{
		if (GI->GetInventory()[i].BaseItemData.ItemName == InItemName)
		{
			TotalAmount = GI->GetInventory()[i].StackAmount;
			break;
		}
	}

	if (TotalAmount >= InAmount)
		return true;
	return false;
}

bool URPGInventoryManagerComponent::CheckIfCanUnequipItemToInventory(FName InItemName) //DONE
{
	if (bIsMultipleStacksAllowed)
		return false;

	bool bSuccess;
	bool bIsFullyStacked;
	int32 Index;

	CheckIfItemIsInInventory(InItemName, bSuccess, bIsFullyStacked, Index);

	if (bSuccess)
		return !bIsFullyStacked;

	return CheckIfThereIsFreeSlotInInventory();
}

int32 URPGInventoryManagerComponent::CheckAmountOfItemsInInventory(FName InItemName) //DONE
{
//	URPGGameInstance* GI = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());

	int32 TotalAmount = 0;

	for (int i = 0; i < GI->GetInventory().Num(); i++)
	{
		if (GI->GetInventory()[i].BaseItemData.ItemName == InItemName)
			TotalAmount += GI->GetInventory()[i].StackAmount;
	}

	return TotalAmount;
}

bool URPGInventoryManagerComponent::CheckIfItemCanBeBought(FName InItemName) //DONE
{
//	URPGGameInstance* GI = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());

	FSoftObjectPath DataTableLoader = TEXT("/Game/DataTables/ItemsDataTable.ItemsDataTable");
	UDataTable* DataTable = Cast<UDataTable>(DataTableLoader.TryLoad());
	FString ContextString;

	if (DataTable)
	{
		FItemsTable* row = DataTable->FindRow<FItemsTable>(InItemName, ContextString);

		if (!row->bCanBeBought || GI->GetGold() < row->BuyValue)
			return false;

		if (bIsMultipleStacksAllowed)
			return true;

		bool bSuccess;
		bool bIsItemFullyStacked;
		int32 Index;

		CheckIfItemIsInInventory(InItemName, bSuccess, bIsItemFullyStacked, Index);

		if (bSuccess)
			return !bIsItemFullyStacked;

		return CheckIfThereIsFreeSlotInInventory();
	}
	
	return false;
}

bool URPGInventoryManagerComponent::CheckIfItemCanBeSold(FName InItemName) //DONE
{
//	URPGGameInstance* GI = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());

	FSoftObjectPath DataTableLoader = TEXT("/Game/DataTables/ItemsDataTable.ItemsDataTable");
	UDataTable* DataTable = Cast<UDataTable>(DataTableLoader.TryLoad());
	FString ContextString;

	if (DataTable)
	{
		FItemsTable* row = DataTable->FindRow<FItemsTable>(InItemName, ContextString);

		if (row->bCanBeSold)
			return true;
	}

	return false;
}

/*				INVENTORY MANAGER			*/
void URPGInventoryManagerComponent::AddItemToInventory(FName InItemName, int32 InAmount) //DONE
{
//	URPGGameInstance* GI = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());

	FSoftObjectPath DataTableLoader = TEXT("/Game/DataTables/ItemsDataTable.ItemsDataTable");
	UDataTable* DataTable = Cast<UDataTable>(DataTableLoader.TryLoad());
	FString ContextString;

	if (DataTable)
	{
		FItemsTable* row = DataTable->FindRow<FItemsTable>(InItemName, ContextString);
		bool bSuccess;
		bool bIsItemFullyStacked;
		int32 Index;

		int32 Surplus;

		if (bIsMultipleStacksAllowed)
		{
			CheckIfItemIsNotFullyStackedInInventory(InItemName, bSuccess, Index);

			if (bSuccess)
			{
				Surplus = InAmount - (GI->GetInventory()[Index].BaseItemData.MaxStackAmount - GI->GetInventory()[Index].StackAmount);
				GI->GetInventory()[Index].StackAmount = FMath::Clamp(InAmount + GI->GetInventory()[Index].StackAmount, 1, GI->GetInventory()[Index].BaseItemData.MaxStackAmount);

				if (Surplus > 0)
					AddItemToInventory(InItemName, Surplus);
			}
			else if (CheckIfThereIsFreeSlotInInventory())
			{
				Surplus = InAmount - row->MaxStackAmount;

				FItemDataStruct Item;

				Item.StackAmount = FMath::Clamp(InAmount, 1, row->MaxStackAmount);
				Item.BaseItemData = URPGCustomFunctionLibrary::GetItemFromDataTable(*row);

				TArray<FItemDataStruct> Inventory = GI->GetInventory();

				Index = Inventory.Add(Item);

				GI->SetInventory(Inventory);

				RefreshInventorySlot(Index);

				if (Surplus > 0)
					AddItemToInventory(InItemName, Surplus);
			}
		}
		else
		{
			CheckIfItemIsInInventory(InItemName, bSuccess, bIsItemFullyStacked, Index);

			if (bSuccess && !bIsItemFullyStacked)
			{
				GI->GetInventory()[Index].StackAmount = FMath::Clamp(InAmount + GI->GetInventory()[Index].StackAmount, 1, GI->GetInventory()[Index].BaseItemData.MaxStackAmount);
				RefreshInventorySlot(Index);
			}
			else if (CheckIfThereIsFreeSlotInInventory())
			{
				FItemDataStruct Item;

				Item.StackAmount = FMath::Clamp(InAmount, 1, row->MaxStackAmount);
				Item.BaseItemData = URPGCustomFunctionLibrary::GetItemFromDataTable(*row);

				TArray<FItemDataStruct> Inventory = GI->GetInventory();

				Index = Inventory.Add(Item);

				GI->SetInventory(Inventory);

				RefreshInventorySlot(Index);
			}
		}
	}
}

void URPGInventoryManagerComponent::RemoveItemFromInventory(FName InItemName, int32 InAmount)
{
//	URPGGameInstance* GI = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());

	bool bSuccess;
	bool bIsItemFullyStacked;
	int32 Index;

	TArray<FItemDataStruct> Inventory = GI->GetInventory();

	if (bIsMultipleStacksAllowed)
	{
		for (int i = 0; i < Inventory.Num(); i++)
		{
			if (InAmount > 0)
			{
				if (Inventory[i].BaseItemData.ItemName == InItemName)
				{
					if (Inventory[i].StackAmount >= InAmount)
					{
						Inventory[i].StackAmount -= InAmount;

						if (Inventory[i].StackAmount > 0)
						{
							RefreshInventorySlot(i);
						}
						else
						{
							Inventory.RemoveAt(i);
							ReleaseInventorySlot(i);
						}

						InAmount = 0;
						RefreshInventorySlotAfterDiscarding(i);

						GI->SetInventory(Inventory);
					}
					else
					{
						InAmount -= Inventory[i].StackAmount;

						Inventory.RemoveAt(i);
						ReleaseInventorySlot(i);

						RefreshInventorySlotAfterDiscarding(i);

						GI->SetInventory(Inventory);
					}
				}
			}
			else
				break;
		}
	}
	else
	{
		CheckIfItemIsInInventory(InItemName, bSuccess, bIsItemFullyStacked, Index);

		if (bSuccess)
		{
			Inventory[Index].StackAmount = Inventory[Index].StackAmount - InAmount;

			if (Inventory[Index].StackAmount > 0)
			{
				RefreshInventorySlot(Index);
			}
			else
			{
				Inventory.RemoveAt(Index);
				ReleaseInventorySlot(Index);
			}

			RefreshInventorySlotAfterDiscarding(Index);
		}
	}
}

void URPGInventoryManagerComponent::RefreshAllInventorySlots()
{
	for (int i = 0; i < InventorySlotsReference.Num(); i++)
	{
		InventorySlotsReference[i]->SetVisibility(ESlateVisibility::Collapsed);
	}

//	URPGGameInstance* GI = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());

	TArray<FItemDataStruct> Inventory = GI->GetInventory();

	for (int i = 0; i < Inventory.Num(); i++)
	{
		GetProperInventorySlotWidget(i)->UpdateItemData(Inventory[i].StackAmount, Inventory[i].BaseItemData);
	}

	RefreshItemDetails();
}

URPGInventorySlotWidget* URPGInventoryManagerComponent::GetProperInventorySlotWidget(int32 InIndex) //DONE
{
	if (IsValid(InventoryScreenReference))
	{
		if (InventorySlotsReference[InIndex]->IsValidLowLevel())
			return InventorySlotsReference[InIndex];

		URPGInventorySlotWidget* ISW = CreateWidget<URPGInventorySlotWidget>(GetWorld(), URPGInventorySlotWidget::StaticClass());

		if (ISW)
		{
			ISW->InventoryManagerReference = this;

			if (ISW->IsValidLowLevel())
			{
				InventorySlotsReference.Add(ISW);

				InventoryScreenReference->Container_Inventory->AddChild(ISW);

				return ISW;
			}
		}
	}

	return nullptr;
}

void URPGInventoryManagerComponent::RefreshInventorySlot(int32 InIndex) //DONE
{
//	URPGGameInstance* GI = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());

	if (GetProperInventorySlotWidget(InIndex)->IsValidLowLevel())
	{
		GetProperInventorySlotWidget(InIndex)->UpdateItemData(GI->GetInventory()[InIndex].StackAmount, GI->GetInventory()[InIndex].BaseItemData);
	}
}

void URPGInventoryManagerComponent::ReleaseInventorySlot(int32 InIndex) //DONE
{
//	URPGGameInstance* GI = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());

	if (InventorySlotsReference[InIndex]->IsValidLowLevel())
	{
		URPGInventorySlotWidget* ISW = InventorySlotsReference[InIndex];
		ISW->SetVisibility(ESlateVisibility::Collapsed);
		InventorySlotsReference.RemoveAt(InIndex);

		InventorySlotsReference.Add(ISW);

		InventoryScreenReference->Container_Inventory->AddChild(ISW);

		if (SelectedItemSlot > GI->GetInventory().Num() - 1)
			SelectedItemSlot = GI->GetInventory().Num() - 1;
		
		RefreshItemDetails();
	}
}

void URPGInventoryManagerComponent::RefreshItemDetails() //DONE
{
//	URPGGameInstance* GI = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());

	if (IsValid(InventoryScreenReference))
	{
		if (GI->GetInventory().Num() > 0)
		{
			InventoryScreenReference->Container_ItemDetails->SetVisibility(ESlateVisibility::Visible);

			InventoryScreenReference->UpdateItemDetails(GI->GetInventory()[SelectedItemSlot].BaseItemData.DisplayName,
														GI->GetInventory()[SelectedItemSlot].BaseItemData.Type,
														GI->GetInventory()[SelectedItemSlot].BaseItemData.Rarity,
														GI->GetInventory()[SelectedItemSlot].BaseItemData.Description);

			InventoryScreenReference->Button_Use->SetIsEnabled(GI->GetInventory()[SelectedItemSlot].BaseItemData.bCanBeUsedInInventory);
		}
		else
			InventoryScreenReference->Container_ItemDetails->SetVisibility(ESlateVisibility::Hidden);
	}
}

void URPGInventoryManagerComponent::ShowDiscardWindow() //DONE
{
//	URPGGameInstance* GI = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());

	if (DiscardItemScreenReference->IsValidLowLevel())
		DiscardItemScreenReference->SetVisibility(ESlateVisibility::Visible);
	else
	{
		DiscardItemScreenReference = CreateWidget<URPGItemDiscardScreenWidget>(GetWorld(), URPGItemDiscardScreenWidget::StaticClass());
		DiscardItemScreenReference->AddToViewport();
	}

	DiscardItemScreenReference->UpdateWindowInfo(GI->GetInventory()[SelectedItemSlot].BaseItemData.ItemName,
		GI->GetInventory()[SelectedItemSlot].BaseItemData.DisplayName,
		CheckAmountOfItemsInInventory(GI->GetInventory()[SelectedItemSlot].BaseItemData.ItemName));
}

void URPGInventoryManagerComponent::RefreshInventorySlotAfterDiscarding(int32 InIndex) //DONE
{
//	URPGGameInstance* GI = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());

	if (GI->GetInventory().Num() > 0)
	{
		URPGInventorySlotWidget* ISW = GetProperInventorySlotWidget(UKismetMathLibrary::SelectInt(InIndex, GI->GetInventory().Num() - 1, InIndex < GI->GetInventory().Num()));

		if (IsValid(ISW))
			InventoryScreenReference->HighlightNewInventoryButton(ISW->Button_InventorySlot);
	}
}

/*				EQUIPMENT CHANGING			*/
TArray<FItemDataStruct> URPGInventoryManagerComponent::GetAllEqupableItems(ItemTypeEnum InItemType) //TODO
{
//	URPGGameInstance* GI = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());

	TArray<FItemDataStruct> Items;
	TArray<FName> AddedItems;

	for (int i = 0; i < GI->GetInventory().Num(); i++)
	{
		if (GI->GetInventory()[i].BaseItemData.Type == InItemType)
		{
			if (!AddedItems.Contains(GI->GetInventory()[i].BaseItemData.ItemName))
			{
				AddedItems.Add(GI->GetInventory()[i].BaseItemData.ItemName);
				Items.Add(GI->GetInventory()[i]);
			}
		}
	}

	return Items;
}

void URPGInventoryManagerComponent::EquipItem(FName InItemName)
{
//	URPGGameInstance* GI = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());

	FBaseItemStruct Item = GetItemStructFromInventory(InItemName);

	if (IsValid(GetOwner()->GetComponentByClass(URPGCharactersManagerComponent::StaticClass())))
	{
		FCharacterInfoStruct* Character = GI->GetCharacters().Find(Cast<URPGCharactersManagerComponent>(GetOwner()->GetComponentByClass(URPGCharactersManagerComponent::StaticClass()))->GetSelectedCharacter());

		//Character
	}
}

FBaseItemStruct URPGInventoryManagerComponent::GetItemStructFromInventory(FName InItemName) //DONE
{
//	URPGGameInstance* GI = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());

	FBaseItemStruct Item;

	for (int i = 0; i < GI->GetInventory().Num(); i++)
	{
		if (GI->GetInventory()[i].BaseItemData.ItemName == InItemName)
			Item = GI->GetInventory()[i].BaseItemData;
	}

	return Item;
}

void URPGInventoryManagerComponent::CalculateStatsComparisonOnEquip(FName InItemName)
{

}

void URPGInventoryManagerComponent::UnequipItem(ItemTypeEnum InItemType)
{

}

void URPGInventoryManagerComponent::ShowAllEquipableItems(ItemTypeEnum InItemType)
{

}

// GetProperEquipmentChangeSlot(int32 InIndex);

	/*				USE ITEM					*/
void URPGInventoryManagerComponent::RefreshUseItemOnCharacterSlots()
{

}

// URPGInventoryManagerComponent::GetProperUseItemOnCharacterSlotWidget(int32 InIndex);

void URPGInventoryManagerComponent::SelectItemToUse()
{

}

void URPGInventoryManagerComponent::UseItemOnCharacter(FName InItemToUse, FName InCharacterName)
{

}

/*				CURRENCY					*/
void URPGInventoryManagerComponent::RefreshGoldAmount()
{

}

void URPGInventoryManagerComponent::ReceiveGold(int32 InGold)
{

}

void URPGInventoryManagerComponent::SpendGold(int32 InGold)
{

}

/*				VENDOR MANAGEMENT			*/
void URPGInventoryManagerComponent::ShowItemsToBuy(int32 InSlotToFocus)
{

}

// URPGInventoryManagerComponent::GetProperVendorSlot(int32 InIndex);

void URPGInventoryManagerComponent::RefreshVendorItemDetails(bool InBShowItemFromInventory)
{

}

void URPGInventoryManagerComponent::ShowItemsToSell(int32 InSlotToFocus)
{

}

void URPGInventoryManagerComponent::BuyItem(FName InItemName)
{

}

void URPGInventoryManagerComponent::SellItem(FName InItemName)
{

}

/*				MACRO						*/
bool URPGInventoryManagerComponent::GetIsCharacterAlive(FName InName)
{
//	URPGGameInstance* GI = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());

	if (GI)
	{
		if (GI->GetCharacters().Find(InName)->CurrentHP > 0)
			return true;
	}
	return false;
}