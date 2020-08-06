// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGCustomFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DataTable.h"

#include "RPG/RPGGameInstance.h"
#include "RPG/RPGCharacter.h"

	/*				Conversion				*/
FText URPGCustomFunctionLibrary::ActionTypeToText(ActionTypeEnum InActionType)
{
	switch (InActionType)
	{
	case ActionTypeEnum::EAttack:
		return FText::FromString("Attack");
		break;
	case ActionTypeEnum::EDefend:
		return FText::FromString("Defend");
		break;
	case ActionTypeEnum::EFlee:
		return FText::FromString("Flee");
		break;
	case ActionTypeEnum::EItems:
		return FText::FromString("Items");
		break;
	case ActionTypeEnum::EMagic:
		return FText::FromString("Magic");
		break;
	default:
		return FText::FromString("");
		break;
	}
}

FText URPGCustomFunctionLibrary::ItemTypeToText(ItemTypeEnum InItemType)
{
	switch (InItemType)
	{
	case ItemTypeEnum::EAccessory:
		return FText::FromString("Accessory");
		break;
	case ItemTypeEnum::EArmor:
		return FText::FromString("Armor");
		break;
	case ItemTypeEnum::EConsumable:
		return FText::FromString("Consumable");
		break;
	case ItemTypeEnum::EKeyItem:
		return FText::FromString("Key Item");
		break;
	case ItemTypeEnum::EMiscellaneous:
		return FText::FromString("Miscellaneous");
		break;
	case ItemTypeEnum::EWeapon:
		return FText::FromString("Weapon");
		break;
	default:
		return FText::FromString("");
		break;
	}
}

//    URPGCustomFunctionLibrary::ItemTypeToImage(ItemTypeEnum InItemType)
//{
//  
//}

FText URPGCustomFunctionLibrary::ItemSubtypeToText(ItemSubtypeEnum InItemSubtype)
{
	switch (InItemSubtype)
	{
	case ItemSubtypeEnum::ENone:
		return FText::FromString("None");
		break;
	case ItemSubtypeEnum::EMeleeWeapon:
		return FText::FromString("Melee Weapon");
		break;
	case ItemSubtypeEnum::ERangedWeapon:
		return FText::FromString("Ranged Weapon");
		break;
	default:
		return FText::FromString("");
		break;
	}
}

FText URPGCustomFunctionLibrary::ItemRarityToText(ItemRarityEnum InItemRarity)
{
	switch (InItemRarity)
	{
	case ItemRarityEnum::ECommon:
		return FText::FromString("Common");
		break;
	case ItemRarityEnum::EEpic:
		return FText::FromString("Epic");
		break;
	case ItemRarityEnum::ELegendary:
		return FText::FromString("Legendary");
		break;
	case ItemRarityEnum::ERare:
		return FText::FromString("Rare");
		break;
	default:
		return FText::FromString("");
		break;
	}
}

FLinearColor URPGCustomFunctionLibrary::ItemRarityToColor(ItemRarityEnum InItemRarity)
{
	switch (InItemRarity)
	{
	case ItemRarityEnum::ECommon:
		return FColor::FromHex("#E4E4E4FF");
		break;
	case ItemRarityEnum::EEpic:
		return FColor::FromHex("#00FFFFFF");
		break;
	case ItemRarityEnum::ELegendary:
		return FColor::FromHex("#FFD700FF");
		break;
	case ItemRarityEnum::ERare:
		return FColor::FromHex("#00FF00FF");
		break;
	default:
		return FColor::FromHex("#FFFFFFFF");
		break;
	}
}

FText URPGCustomFunctionLibrary::StatTypeToText(StatsEnum InStatType)
{
	switch (InStatType)
	{
	case StatsEnum::EDexterity:
		return FText::FromString("Dexterity");
		break;
	case StatsEnum::EHP:
		return FText::FromString("HP");
		break;
	case StatsEnum::EInitiative:
		return FText::FromString("Initiative");
		break;
	case StatsEnum::ELuck:
		return FText::FromString("Luck");
		break;
	case StatsEnum::EMagic:
		return FText::FromString("Magic");
		break;
	case StatsEnum::EMP:
		return FText::FromString("MP");
		break;
	case StatsEnum::ESpirit:
		return FText::FromString("Spirit");
		break;
	case StatsEnum::EStrength:
		return FText::FromString("Strength");
		break;
	case StatsEnum::EVitality:
		return FText::FromString("Vitality");
		break;
	default:
		return FText::FromString("");
		break;
	}
}

FText URPGCustomFunctionLibrary::DerivedStatTypeToText(DerivedStatsEnum InDerivedStatType)
{
	switch (InDerivedStatType)
	{
	case DerivedStatsEnum::EAttack:
		return FText::FromString("Attack");
		break;
	case DerivedStatsEnum::EAttackChance:
		return FText::FromString("Attack Chance");
		break;
	case DerivedStatsEnum::EDarkResistance:
		return FText::FromString("Dark Resistance");
		break;
	case DerivedStatsEnum::EDefense:
		return FText::FromString("Defense");
		break;
	case DerivedStatsEnum::EDefenseChance:
		return FText::FromString("Defense Chance");
		break;
	case DerivedStatsEnum::EEarthResistance:
		return FText::FromString("Earth Resistance");
		break;
	case DerivedStatsEnum::EFireResistance:
		return FText::FromString("Fire Resistance");
		break;
	case DerivedStatsEnum::EIceResistance:
		return FText::FromString("Ice Resistance");
		break;
	case DerivedStatsEnum::ELightResistance:
		return FText::FromString("Light Resistance");
		break;
	case DerivedStatsEnum::EMagicPower:
		return FText::FromString("Magic Power");
		break;
	case DerivedStatsEnum::EMagicResistance:
		return FText::FromString("Magic Resistance");
		break;
	case DerivedStatsEnum::EThunderResistance:
		return FText::FromString("Thunder Resistance");
		break;
	case DerivedStatsEnum::EWaterResistance:
		return FText::FromString("Water Resistance");
		break;
	case DerivedStatsEnum::EWindResistance:
		return FText::FromString("Wind Resistance");
		break;
	default:
		return FText::FromString("");
		break;
	}
}

	/*				Stats				    */
int32 URPGCustomFunctionLibrary::GetExperienceNeededToNextLevel(FName InHeroName, int32 InCurrentLevel, int32 InCurrentXP)
{
	FSoftObjectPath DataTableLoader = TEXT("/Game/DataTables/ExperienceDataTable.ExperienceDataTable");
	UDataTable* datatable = Cast<UDataTable>(DataTableLoader.TryLoad());

	if (datatable)
	{
		FHeroesTable* ht = datatable->FindRow<FHeroesTable>(*FString::FromInt(InCurrentLevel + 1), "");

		if (InHeroName == "Hero1")
		{
			UE_LOG(LogTemp, Warning, TEXT("%d"), ht->Hero1 - InCurrentXP);
			return ht->Hero1 - InCurrentXP;
		}
		else if (InHeroName == "Hero2")
		{
			UE_LOG(LogTemp, Warning, TEXT("%d"), ht->Hero2 - InCurrentXP);
			return ht->Hero2 - InCurrentXP;
		}
		else if (InHeroName == "Hero3")
		{
			UE_LOG(LogTemp, Warning, TEXT("%d"), ht->Hero3 - InCurrentXP);
			return ht->Hero3 - InCurrentXP;
		}
		else if (InHeroName == "Hero4")
		{
			UE_LOG(LogTemp, Warning, TEXT("%d"), ht->Hero4 - InCurrentXP);
			return ht->Hero3 - InCurrentXP;
		}
	}
	
	return 1;
}

	/*				SaveAndLoad				*/
/*void URPGCustomFunctionLibrary::ChangeMap(AActor* InCharacter, FName InMapName, FName InSpawnPointName)
{
	ARPGCharacter* Character = Cast<ARPGCharacter>(InCharacter);
	UWorld* World = Character->GetWorld();
	
	if (World)
	{
		URPGGameInstance* GI = Cast<URPGGameInstance>(World->GetGameInstance());

		if (GI)
		{
			GI->SetWorldMapName(InMapName);
			GI->SetWorldMapSpawnPointName(InSpawnPointName);

			FLatentActionInfo LatentInfo;

			UGameplayStatics::GetStreamingLevel(World, GI->GetWorldMapName())->SetShouldBeVisible(false);
			UGameplayStatics::LoadStreamLevel(World, InMapName, false, false, LatentInfo);
			UGameplayStatics::UnloadStreamLevel(World, GI->GetWorldMapName(), LatentInfo, false);
			UGameplayStatics::GetStreamingLevel(World, InMapName)->SetShouldBeVisible(true);
		}
	}
}*/

	/*				DisplayName				*/
FText URPGCustomFunctionLibrary::GetActionDisplayName(FName InActionName)
{
	return FText::FromString("");
}

FText URPGCustomFunctionLibrary::GetItemDisplayName(FName InItemName)
{
	return FText::FromString("");
}

FBaseItemStruct URPGCustomFunctionLibrary::GetItemFromDataTable(FItemsTable InItem)
{
	FBaseItemStruct Item;

	Item.ItemName = InItem.Name;
	Item.DisplayName = InItem.DisplayName;
	Item.Type = InItem.ItemType;
	Item.Rarity = InItem.ItemRarity;
	Item.bCanBeUsedInBattle = InItem.bCanBeUsedInBattle;
	Item.bCanBeUsedInInventory = InItem.bCanBeUsedInInventory;
	Item.MaxStackAmount = InItem.MaxStackAmount;
	Item.BuyValue = InItem.BuyValue;
	Item.SellValue = InItem.SellValue;
	Item.Stats = InItem.Stats;
	Item.DerivedStats = InItem.DerivedStats;
	Item.Icon = InItem.Icon;
	Item.bCanBeBought = InItem.bCanBeBought;
	Item.bCanBeSold = InItem.bCanBeSold;

	return Item;
}