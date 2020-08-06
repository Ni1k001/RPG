// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGCharactersManagerComponent.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "UMG/Public/Components/HorizontalBox.h"
#include "UMG/Public/Components/TextBlock.h"
#include "UMG/Public/Components/VerticalBox.h"
#include "UMG/Public/Components/WrapBox.h"

#include "RPG/RPGCharacter.h"
#include "RPG/RPGCustomFunctionLibrary.h"
#include "RPG/RPGDataTables.h"
#include "RPG/RPGGameInstance.h"

#include "RPG/battle/RPGBattleCharacter.h"

#include "RPG/components/RPGBattleManagerComponent.h"
#include "RPG/components/RPGBattleCharacterStatsComponent.h"

#include "RPG/widgets/actions/RPGCharacterActionsSlotWidget.h"
#include "RPG/widgets/actions/RPGCharacterActionsWidget.h"
#include "RPG/widgets/actions/RPGOwnedActionSlotWidget.h"

#include "RPG/widgets/overview/RPGCharacterOverviewScreenWidget.h"
#include "RPG/widgets/overview/RPGCharacterOverviewSlotWidget.h"
#include "RPG/widgets/overview/RPGStatSlotWidget.h"

#include "RPG/widgets/characterselection/RPGCharacterEquipmentSlotWidget.h"
#include "RPG/widgets/characterselection/RPGCharacterSelectScreenWidget.h"
#include "RPG/widgets/characterselection/RPGCharacterSelectionSlotWidget.h"


// Sets default values for this component's properties
URPGCharactersManagerComponent::URPGCharactersManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URPGCharactersManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	while (!GI)
	{
		GI = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());
	}
}


// Called every frame
void URPGCharactersManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int32 URPGCharactersManagerComponent::GetMaxCharactersAmountInParty()
{
	return MaxCharactersAmountInParty;
}

void URPGCharactersManagerComponent::SetMaxCharactersAmountInParty(int32 InMaxCharactersAmountInParty)
{
	MaxCharactersAmountInParty = InMaxCharactersAmountInParty;
}

int32 URPGCharactersManagerComponent::GetMaxCharactersAmountInCollection()
{
	return MaxCharactersAmountInCollection;
}

void URPGCharactersManagerComponent::SetMaxCharactersAmountInCollection(int32 InMaxCharactersAmountInCollection)
{
	MaxCharactersAmountInCollection = InMaxCharactersAmountInCollection;
}

int32 URPGCharactersManagerComponent::GetCharacterMaxLevel()
{
	return CharacterMaxLevel;
}

void URPGCharactersManagerComponent::SetCharacterMaxLevel(int32 InCharacterMaxLevel)
{
	CharacterMaxLevel = InCharacterMaxLevel;
}

TArray<URPGCharacterOverviewSlotWidget*> URPGCharactersManagerComponent::GetCharactersOverviewSlotsReference()
{
	return CharacterOverviewSlotsReference;
}

void URPGCharactersManagerComponent::SetCharactersOverviewSlotsReference(TArray<URPGCharacterOverviewSlotWidget*> InCharacterOverviewSlotsReference)
{
	CharacterOverviewSlotsReference = InCharacterOverviewSlotsReference;
}

TArray<URPGCharacterSelectionSlotWidget*> URPGCharactersManagerComponent::GetCurrentTeamMembersSlots()
{
	return CurrentTeamMembersSlots;
}

void URPGCharactersManagerComponent::SetCurrentTeamMembersSlots(TArray<URPGCharacterSelectionSlotWidget*> InCurrentTeamMembersSlots)
{
	CurrentTeamMembersSlots = InCurrentTeamMembersSlots;
}

TArray<URPGCharacterSelectionSlotWidget*> URPGCharactersManagerComponent::GetOtherMembersSlots()
{
	return OtherMembersSlots;
}

void URPGCharactersManagerComponent::SetOtherMembersSlots(TArray<URPGCharacterSelectionSlotWidget*> InOtherMembersSlots)
{
	OtherMembersSlots = InOtherMembersSlots;
}

URPGCharacterOverviewScreenWidget* URPGCharactersManagerComponent::GetCharacterOverviewScreenReference()
{
	return CharacterOverviewScreenReference;
}

void URPGCharactersManagerComponent::SetCharacterOverviewScreenReference(URPGCharacterOverviewScreenWidget* InCharacterOverviewScreenReference)
{
	CharacterOverviewScreenReference = InCharacterOverviewScreenReference;
}

URPGCharacterSelectScreenWidget* URPGCharactersManagerComponent::GetCharacterSelectionScreenReference()
{
	return CharacterSelectionScreenReference;
}

void URPGCharactersManagerComponent::SetCharacterSelectionScreenReference(URPGCharacterSelectScreenWidget* InCharacterSelectionScreenReference)
{
	CharacterSelectionScreenReference = InCharacterSelectionScreenReference;
}

FName URPGCharactersManagerComponent::GetSelectedCharacter()
{
	return SelectedCharacter;
}

void URPGCharactersManagerComponent::SetSelectedCharacter(FName InSelectedCharacter)
{
	SelectedCharacter = InSelectedCharacter;
}

URPGCharacterActionsWidget* URPGCharactersManagerComponent::GetCharacterActionScreenReference()
{
	return CharacterActionScreenReference;
}

void URPGCharactersManagerComponent::SetCharacterActionScreenReference(URPGCharacterActionsWidget* InCharacterActionScreenReference)
{
	CharacterActionScreenReference = InCharacterActionScreenReference;
}

TArray<URPGCharacterActionsSlotWidget*> URPGCharactersManagerComponent::GetCharacterSlotsInActionScreenReference()
{
	return CharacterSlotsInActionScreenReference;
}

void URPGCharactersManagerComponent::SetCharacterSlotsInActionScreenReference(TArray<URPGCharacterActionsSlotWidget*> InCharacterSlotsInActionScreenReference)
{
	CharacterSlotsInActionScreenReference = InCharacterSlotsInActionScreenReference;
}

TArray<URPGOwnedActionSlotWidget*> URPGCharactersManagerComponent::GetOwnedActionsSlotsReference()
{
	return OwnedActionsSlotsReference;
}

void URPGCharactersManagerComponent::SetOwnedActionsSlotsReference(TArray<URPGOwnedActionSlotWidget*> InOwnedActionsSlotsReference)
{
	OwnedActionsSlotsReference = InOwnedActionsSlotsReference;
}

FName URPGCharactersManagerComponent::GetSelectedAction()
{
	return SelectedAction;
}

void URPGCharactersManagerComponent::SetSelectedAction(FName InSelectedAction)
{
	SelectedAction = InSelectedAction;
}

/*				Initialization				*/
void URPGCharactersManagerComponent::CreateReferenceToCharacterOverviewScreen()
{
	TArray<UUserWidget*> FoundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, URPGCharacterOverviewScreenWidget::StaticClass(), false);

	if (FoundWidgets.IsValidIndex(0))
	{
		CharacterOverviewScreenReference = Cast<URPGCharacterOverviewScreenWidget>(FoundWidgets[0]);

		for (int i = 0; i < MaxCharactersAmountInParty; i++)
		{
			URPGCharacterOverviewSlotWidget* COS = CreateWidget<URPGCharacterOverviewSlotWidget>(GetWorld(), URPGCharacterOverviewSlotWidget::StaticClass());
			if (IsValid(COS))
			{
				CharacterOverviewSlotsReference.Add(COS);
				CharacterOverviewScreenReference->Container_CharacterSlots->AddChild(COS);
			}
		}

		RefreshCharacterOverviewSlots();
	}
}

void URPGCharactersManagerComponent::CreateReferenceToCharacterSelectonScreen()
{
	TArray<UUserWidget*> FoundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, URPGCharacterSelectScreenWidget::StaticClass(), false);

	if (FoundWidgets.IsValidIndex(0))
	{
		CharacterSelectionScreenReference = Cast<URPGCharacterSelectScreenWidget>(FoundWidgets[0]);

		for (int i = 0; i < MaxCharactersAmountInParty; i++)
		{
			URPGCharacterSelectionSlotWidget* CSS = CreateWidget<URPGCharacterSelectionSlotWidget>(GetWorld(), URPGCharacterSelectionSlotWidget::StaticClass());

			CurrentTeamMembersSlots.Add(CSS);
			CharacterSelectionScreenReference->Container_CurrentTeam->AddChild(CSS);
		}

		for (int i = 0; i < MaxCharactersAmountInCollection; i++)
		{
			URPGCharacterSelectionSlotWidget* CSS = CreateWidget<URPGCharacterSelectionSlotWidget>(GetWorld(), URPGCharacterSelectionSlotWidget::StaticClass());
			if (IsValid(CSS))
			{
				OtherMembersSlots.Add(CSS);
				CharacterSelectionScreenReference->Container_OtherCharacters->AddChild(CSS);
			}
		}

		RefreshCharacterSelectionSlots();
		RefreshSelectedCharacterData();
		
		CharacterSelectionScreenReference->HighlightNewCharacterSelectionButton(CurrentTeamMembersSlots[0]->Button_CharacterSlot);
	}
}

void URPGCharactersManagerComponent::CreateReferenceToActionsScreen()
{
	TArray<UUserWidget*> FoundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, URPGCharacterActionsWidget::StaticClass(), false);

	if (IsValid(FoundWidgets[0]))
	{
		CharacterActionScreenReference = Cast<URPGCharacterActionsWidget>(FoundWidgets[0]);

		for (int i = 0; i < MaxCharactersAmountInParty; i++)
		{
			URPGCharacterActionsSlotWidget* CAS = CreateWidget<URPGCharacterActionsSlotWidget>(GetWorld(), URPGCharacterActionsSlotWidget::StaticClass());

			CharacterSlotsInActionScreenReference.Add(CAS);

			CAS->SetPadding(FMargin(8.f, 8.f, 8.f, 8.f));

			CharacterActionScreenReference->Container_CurentPartySlots->AddChild(CAS);
		}

		RefreshCharactersSlotsInActionScreen();
	}
}

/*				Party						*/
void URPGCharactersManagerComponent::RefreshCharacterOverviewSlots() //DONE
{
	for (int i = 0; i < CharacterOverviewSlotsReference.Num(); i++)
	{
		if (GI->GetParty().IsValidIndex(i))
		{
			if (GI->GetCharacters().Contains(GI->GetParty()[i].Name))
			{
				FCharacterInfoStruct Character = *GI->GetCharacters().Find(GI->GetParty()[i].Name);

				CharacterOverviewSlotsReference[i]->SetVisibility(ESlateVisibility::Visible);
				CharacterOverviewSlotsReference[i]->UpdateCharacterMainInfo(Character.Name, Character.DisplayName, Character.CurrentLevel, Character.CurrentExperience);
				CharacterOverviewSlotsReference[i]->UpdateCharacterStats(Character.Stats);
				CharacterOverviewSlotsReference[i]->UpdateCharacterEquipment(Character.Equipment);

				continue;
			}
		}

		CharacterOverviewSlotsReference[i]->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void URPGCharactersManagerComponent::RefreshCharacterSelectionSlots() //DONE
{
	for (int i = 0; i < CurrentTeamMembersSlots.Num(); i++)
	{
		if (!GI->GetParty().IsValidIndex(i))
		{
			FName name = *FString(TEXT("None"));
			CurrentTeamMembersSlots[i]->UpdateSlotData(name, false);
			continue;
		}
		
		FCharacterInfoStruct Character = *GI->GetCharacters().Find(GI->GetParty()[i].Name);

		CurrentTeamMembersSlots[i]->UpdateSlotData(Character.Name, true);

		if (SelectedCharacter == Character.Name)
			CharacterSelectionScreenReference->HighlightNewCharacterSelectionButton(CurrentTeamMembersSlots[i]->Button_CharacterSlot);
	}

	for (int i = 0; i < OtherMembersSlots.Num(); i++)
	{
		FName name = *FString(TEXT("None"));
		OtherMembersSlots[i]->UpdateSlotData(name, false);
	}

	TArray<FName> CharactersNames;
	GI->GetCharacters().GetKeys(CharactersNames);

	int32 CollectionIndex = 0;

	for (int i = 0; i < CharactersNames.Num(); i++)
	{
		bool bSuccess;
		int32 Index;
		CheckIfCharacterIsInParty(CharactersNames[i], bSuccess, Index);

		if (bSuccess)
		{
			FCharacterInfoStruct Character = *GI->GetCharacters().Find(CharactersNames[i]);

			OtherMembersSlots[CollectionIndex]->UpdateSlotData(Character.Name, true);
			CollectionIndex++;

			CharacterSelectionScreenReference->HighlightNewCharacterSelectionButton(OtherMembersSlots[i]->Button_CharacterSlot);
		}
	}
}

void URPGCharactersManagerComponent::AddCharacterToParty(FName InName) //DONE
{
	TArray<FPartySlotStruct> Party = GI->GetParty();
	if (Party.Num() < MaxCharactersAmountInParty)
	{
		bool bSuccess;
		int32 Index;

		CheckIfCharacterIsInParty(InName, bSuccess, Index);

		if (bSuccess)
		{
			FPartySlotStruct NewPartyMember;
			NewPartyMember.Name = InName;

			Party.Add(NewPartyMember);
			GI->SetParty(Party);

			RefreshCharacterOverviewSlots();
		}
	}
}

void URPGCharactersManagerComponent::RemoveCharacterFromParty(FName InName) //DONE
{
	TArray<FPartySlotStruct> Party = GI->GetParty();
	if (Party.Num() > 1)
	{
		bool bSuccess;
		int32 Index;

		CheckIfCharacterIsInParty(InName, bSuccess, Index);

		if (bSuccess)
		{
			Party.RemoveAt(Index);
			GI->SetParty(Party);

			RefreshCharacterOverviewSlots();
		}
	}
}

void URPGCharactersManagerComponent::CheckIfCharacterIsInParty(FName InCharacter, bool& OutBIsSuccess, int32& OutIndex) //DONE
{
	for (int i = 0; i < GI->GetParty().Num(); i++)
	{
		if (GI->GetParty()[i].Name == InCharacter)
		{
			OutBIsSuccess = true;
			OutIndex = i;
			return;
		}
	}

	OutBIsSuccess = false;
	OutIndex = 0;
}

/*				Characters Management		*/
void URPGCharactersManagerComponent::AddNewCharacterToCollection(FCharacterInfoStruct InCharacter) //DONE
{
	TMap<FName, FCharacterInfoStruct> Characters = GI->GetCharacters();

	if (Characters.Num() < MaxCharactersAmountInCollection)
	{
		FSoftObjectPath DataTableLoader = TEXT("/Game/DataTables/ItemsDataTable.ItemsDataTable");
		UDataTable* DataTable = Cast<UDataTable>(DataTableLoader.TryLoad());
		FString ContextString;
		if (DataTable)
		{
			Characters.Add(InCharacter.Name, InCharacter);

			TArray<ItemTypeEnum> Items;
			InCharacter.Equipment.GetKeys(Items);

			for (int i = 0; i < Items.Num(); i++)
			{
				FItemsTable* row = DataTable->FindRow<FItemsTable>(InCharacter.Equipment.Find(Items[i])->ItemName, ContextString);

				InCharacter.Equipment.Add(row->ItemType, URPGCustomFunctionLibrary::GetItemFromDataTable(*row));
				
				IncreaseCharacterStats(InCharacter.Name, row->Stats, row->DerivedStats);
			}

			FCharacterInfoStruct Character = *Characters.Find(InCharacter.Name);
			Character.Equipment = InCharacter.Equipment;

			Characters.Add(InCharacter.Name, Character);
			GI->SetCharacters(Characters);
		}
	}
}

void URPGCharactersManagerComponent::IncreaseCharacterStats(FName InName, TMap<StatsEnum, float> InStats, TMap<DerivedStatsEnum, float> InDerivedStats) //DONE
{
	TMap<FName, FCharacterInfoStruct> Characters = GI->GetCharacters();

	FCharacterInfoStruct* Character = Characters.Find(InName);

	TArray<StatsEnum> Stats;
	Character->Stats.GetKeys(Stats);

	TArray<DerivedStatsEnum> DerivedStats;
	Character->DerivedStats.GetKeys(DerivedStats);

	for (int i = 0; i < Stats.Num(); i++)
	{
		Character->Stats.Add(Stats[i], *Character->Stats.Find(Stats[i]) + *InStats.Find(Stats[i]));

		URPGBattleManagerComponent* BMC = Cast<URPGBattleManagerComponent>(GetOwner()->GetComponentByClass(URPGBattleManagerComponent::StaticClass()));

		TArray<ARPGBattleCharacter*> BMCCharacters = BMC->GetPlayerCharacters();

		switch (Stats[i])
		{
		case StatsEnum::EHP:
			
			for (int j = 0; j < BMCCharacters.Num(); j++)
			{
				if (InName == BMCCharacters[j]->GetCharacterStats()->GetHardcodedName())
				{
					URPGBattleCharacterStatsComponent* BCS = BMCCharacters[j]->GetCharacterStats();

					BCS->SetCurrentHP(BCS->GetCurrentHP() + *InStats.Find(StatsEnum::EHP));

					BMCCharacters[j]->SetCharacterStats(BCS);
				}
			}

			BMC->SetPlayerCharacters(BMCCharacters);
			break;
		case StatsEnum::EMP:
			for (int j = 0; j < BMCCharacters.Num(); j++)
			{
				if (InName == BMCCharacters[j]->GetCharacterStats()->GetHardcodedName())
				{
					URPGBattleCharacterStatsComponent* BCS = BMCCharacters[j]->GetCharacterStats();

					BCS->SetCurrentMP(BCS->GetCurrentMP() + *InStats.Find(StatsEnum::EMP));

					BMCCharacters[j]->SetCharacterStats(BCS);
				}
			}

			BMC->SetPlayerCharacters(BMCCharacters);
			break;
		default:
			break;
		}
	}

	for (int i = 0; i < DerivedStats.Num(); i++)
	{
		Character->DerivedStats.Add(DerivedStats[i], *Character->DerivedStats.Find(DerivedStats[i]) + *InDerivedStats.Find(DerivedStats[i]));

		URPGBattleManagerComponent* BMC = Cast<URPGBattleManagerComponent>(GetOwner()->GetComponentByClass(URPGBattleManagerComponent::StaticClass()));

		TArray<ARPGBattleCharacter*> BMCCharacters = BMC->GetPlayerCharacters();
		for (int j = 0; j < BMCCharacters.Num(); j++)
		{
			if (InName == BMCCharacters[j]->GetCharacterStats()->GetHardcodedName())
			{
				URPGBattleCharacterStatsComponent* BCS = BMCCharacters[j]->GetCharacterStats();

				TMap<DerivedStatsEnum, float> BCSDerivedStats = BCS->GetDerivedStats();
				BCSDerivedStats.Add(DerivedStats[i], *BCS->GetDerivedStats().Find(DerivedStats[i]) + *InDerivedStats.Find(DerivedStats[i]));

				BCS->SetDerivedStats(BCSDerivedStats);

				BMCCharacters[j]->SetCharacterStats(BCS);
			}
		}

		BMC->SetPlayerCharacters(BMCCharacters);
	}

	Characters.Add(InName, *Character);

	GI->SetCharacters(Characters);
}

void URPGCharactersManagerComponent::DecreaseCharacterStats(FName InName, TMap<StatsEnum, float> InStats, TMap<DerivedStatsEnum, float> InDerivedStats) //DONE
{
	TMap<FName, FCharacterInfoStruct> Characters = GI->GetCharacters();

	FCharacterInfoStruct* Character = Characters.Find(InName);

	TArray<StatsEnum> Stats;
	Character->Stats.GetKeys(Stats);

	TArray<DerivedStatsEnum> DerivedStats;
	Character->DerivedStats.GetKeys(DerivedStats);

	for (int i = 0; i < Stats.Num(); i++)
		Character->Stats.Add(Stats[i], *Character->Stats.Find(Stats[i]) - *InStats.Find(Stats[i]));

	for (int i = 0; i < DerivedStats.Num(); i++)
		Character->DerivedStats.Add(DerivedStats[i], *Character->DerivedStats.Find(DerivedStats[i]) - *InDerivedStats.Find(DerivedStats[i]));

	Characters.Add(InName, *Character);

	GI->SetCharacters(Characters);
}

void URPGCharactersManagerComponent::RestoreHP(FName InName, float InAmount) //DONE
{
	TMap<FName, FCharacterInfoStruct> Characters = GI->GetCharacters();

	FCharacterInfoStruct* Character = Characters.Find(InName);

	Character->Stats.Add(StatsEnum::EHP, FMath::Clamp(InAmount + Character->CurrentHP, 0.f, *Character->Stats.Find(StatsEnum::EHP)));

	Characters.Add(InName, *Character);

	GI->SetCharacters(Characters);
}

void URPGCharactersManagerComponent::RestoreMP(FName InName, float InAmount) //DONE
{
	TMap<FName, FCharacterInfoStruct> Characters = GI->GetCharacters();

	FCharacterInfoStruct* Character = Characters.Find(InName);

	Character->Stats.Add(StatsEnum::EMP, FMath::Clamp(InAmount + Character->CurrentMP, 0.f, *Character->Stats.Find(StatsEnum::EMP)));

	Characters.Add(InName, *Character);

	GI->SetCharacters(Characters);
}

void URPGCharactersManagerComponent::RecoverAllCharacterToFull() //DONE
{
	TMap<FName, FCharacterInfoStruct> Characters = GI->GetCharacters();

	TArray<FName> CharactersNames;
	Characters.GetKeys(CharactersNames);

	for (int i = 0; i < CharactersNames.Num(); i++)
	{
		FCharacterInfoStruct* Character = Characters.Find(CharactersNames[i]);

		Character->CurrentHP = *Character->Stats.Find(StatsEnum::EHP);
		Character->CurrentMP = *Character->Stats.Find(StatsEnum::EMP);

		Characters.Add(CharactersNames[i], *Character);

		RefreshCharacterOverviewSlots();
		RefreshCharacterSelectionSlots();
	}
}

void URPGCharactersManagerComponent::RefreshSelectedCharacterData()
{
	if (!GI->GetCharacters().Contains(SelectedCharacter))
	{
		SelectedCharacter = GI->GetParty()[0].Name;
	}

	FCharacterInfoStruct Character = *GI->GetCharacters().Find(SelectedCharacter);

	TArray<URPGStatSlotWidget*> SSW = CharacterSelectionScreenReference->GetStatSlotsReference();
	for (int i = 0; i < SSW.Num(); i++)
		SSW[i]->TextBlock_StatValue->SetText(FText::FromString(FString::SanitizeFloat(*Character.Stats.Find(SSW[i]->AssignedStatType))));

	CharacterSelectionScreenReference->SetStatSlotsReference(SSW);

	TArray<URPGCharacterEquipmentSlotWidget*> CESW = CharacterSelectionScreenReference->GetEquipmentSlotsReference();
	for (int i = 0; i < CESW.Num(); i++)
		CESW[i]->UpdateSlotInfo(*Character.Equipment.Find(CESW[i]->GetAssignedItemType()));

	CharacterSelectionScreenReference->SetEquipmentSlotsReference(CESW);

	CharacterSelectionScreenReference->TextBlock_CharacterName->SetText(Character.DisplayName);
	CharacterSelectionScreenReference->TextBlock_Level->SetText(FText::FromString("Level " + FString::FromInt(Character.CurrentLevel)));
	CharacterSelectionScreenReference->TextBlock_Exp->SetText(FText::FromString("Exp " + FString::FromInt(Character.CurrentExperience) + " / " + FString::FromInt(URPGCustomFunctionLibrary::GetExperienceNeededToNextLevel(Character.Name, Character.CurrentLevel, Character.CurrentExperience))));
}

void URPGCharactersManagerComponent::ShowStatsComparison(TMap<StatsEnum, float> InStats, TMap<DerivedStatsEnum, float> InDerivedStats) //?
{
	TArray<URPGStatSlotWidget*> SSW = CharacterSelectionScreenReference->GetStatSlotsReference();
	FCharacterInfoStruct Character = *GI->GetCharacters().Find(SelectedCharacter);

	for (int i = 0; i < SSW.Num(); i++)
	{
		float Stat = *InStats.Find(SSW[i]->AssignedStatType);
		float CharacterStat = *Character.Stats.Find(SSW[i]->AssignedStatType);

		if (Stat > CharacterStat)
			SSW[i]->SetComparisonPartToHigher(Stat);
		else if (Stat == CharacterStat)
			SSW[i]->SetComparisonPartToEqual(Stat);
		else
			SSW[i]->SetComparisonPartToLower(Stat);
	}

	CharacterSelectionScreenReference->SetStatSlotsReference(SSW);
}

void URPGCharactersManagerComponent::HideStatsComparison() //DONE
{
	TArray<URPGStatSlotWidget*> SSW = CharacterSelectionScreenReference->GetStatSlotsReference();

	for (int i = 0; i < SSW.Num(); i++)
		SSW[i]->SetVisibility(ESlateVisibility::Hidden);

	CharacterSelectionScreenReference->SetStatSlotsReference(SSW);
	CharacterSelectionScreenReference->UnhighlightSelectEquipmentButton();
}

/*				Leveling					*/
void URPGCharactersManagerComponent::AddExperienceToCharacter(FName InName, int32 InAmount) //DONE
{
	TMap<FName, FCharacterInfoStruct> Characters = GI->GetCharacters();

	FCharacterInfoStruct* Character = Characters.Find(InName);

	while (InAmount >= URPGCustomFunctionLibrary::GetExperienceNeededToNextLevel(InName, Character->CurrentLevel, Character->CurrentExperience))
	{
		InAmount -= URPGCustomFunctionLibrary::GetExperienceNeededToNextLevel(InName, Character->CurrentLevel, Character->CurrentExperience);
		LevelUpCharacter(InName);
	}

	Character->CurrentExperience += InAmount;

	Characters.Add(InName, *Character);

	GI->SetCharacters(Characters);
}

void URPGCharactersManagerComponent::LevelUpCharacter(FName InName) 
{
	TMap<FName, FCharacterInfoStruct> Characters = GI->GetCharacters();

	FCharacterInfoStruct* Character = Characters.Find(InName);

	Character->CurrentLevel++;

	Characters.Add(InName, *Character);

	IncreaseCharacterStats(InName, Character->Stats, Character->DerivedStats);

	GI->SetCharacters(Characters);

	//
}

/*				Actions						*/
void URPGCharactersManagerComponent::RefreshCharactersSlotsInActionScreen()
{
	for (int i = 0; i < CharacterSlotsInActionScreenReference.Num(); i++)
	{
		if (!GI->GetParty().IsValidIndex(i))
			CharacterSlotsInActionScreenReference[i]->SetVisibility(ESlateVisibility::Collapsed);

		CharacterSlotsInActionScreenReference[i]->SetVisibility(ESlateVisibility::Visible);
		CharacterSlotsInActionScreenReference[i]->UpdateSlotData(GI->GetParty()[i].Name, true, GI->GetCharacters().Find(GI->GetParty()[i].Name)->Icon);
	}
}

void URPGCharactersManagerComponent::RefreshSelectedCharacterActionsData()
{
	if (!GI->GetCharacters().Find(SelectedCharacter))
		SelectedCharacter = GI->GetParty()[0].Name;

	FCharacterInfoStruct Character = *GI->GetCharacters().Find(SelectedCharacter);

	for (int i = 0; i < OwnedActionsSlotsReference.Num(); i++)
		OwnedActionsSlotsReference[i]->SetVisibility(ESlateVisibility::Collapsed);

	CharacterActionScreenReference->TextBlock_CharacterName->SetText(Character.DisplayName);

	TArray<FName> Actions;
	Character.CharacterActions.GetKeys(Actions);

	for (int i = 0; i < Actions.Num(); i++)
	{
		URPGOwnedActionSlotWidget* OAS = GetProperActionSlot(i);

		//
	}
}

URPGOwnedActionSlotWidget* URPGCharactersManagerComponent::GetProperActionSlot(int32 InIndex)
{
	if (IsValid(CharacterActionScreenReference))
	{
		if (OwnedActionsSlotsReference.IsValidIndex(InIndex))
			return OwnedActionsSlotsReference[InIndex];

		URPGOwnedActionSlotWidget* OAS = CreateWidget<URPGOwnedActionSlotWidget>(GetWorld(), URPGOwnedActionSlotWidget::StaticClass());

		if (IsValid(OAS))
		{
			OwnedActionsSlotsReference.Add(OAS);
			CharacterActionScreenReference->Container_Actions->AddChild(OAS);

			return OAS;
		}
	}

	return nullptr;
}

void URPGCharactersManagerComponent::RefreshSelectedActionData(FName InName)
{
	//
}

void URPGCharactersManagerComponent::LearnNewAction(FName InCharacterName, FName InActionName, bool InBUpdateIfIsAlreadyLearned)
{
	TMap<FName, FCharacterInfoStruct> Characters = GI->GetCharacters();
	FCharacterInfoStruct Character = *Characters.Find(InCharacterName);
	TMap<FName, int32> Actions = Character.CharacterActions;

	if (Actions.Contains(InActionName))
	{
		if (InBUpdateIfIsAlreadyLearned)
			UpgradeAction(InCharacterName, InActionName);
	}
	else
	{
		Actions.Add(InActionName, 1);

		Character.CharacterActions = Actions;
		Characters.Add(Character.Name, Character);

		GI->SetCharacters(Characters);
	}
}

void URPGCharactersManagerComponent::UpgradeAction(FName InCharacterName, FName InActionName)
{
	TMap<FName, FCharacterInfoStruct> Characters = GI->GetCharacters();
	FCharacterInfoStruct Character = *Characters.Find(InCharacterName);
	
	if (Character.ActionPoints > 0)
	{
		TMap<FName, int32> Actions = Character.CharacterActions;

		if (Actions.Contains(InActionName))
		{
			//
		}
	}
}

void URPGCharactersManagerComponent::DegradeAction(FName InCharacterName, FName InActionName, bool InBRestoreActionPoint)
{
	TMap<FName, FCharacterInfoStruct> Characters = GI->GetCharacters();
	FCharacterInfoStruct Character = *Characters.Find(InCharacterName);
	TMap<FName, int32> Actions = Character.CharacterActions;

	if (Actions.Contains(InActionName))
	{
		int32 ActionPointsRef = *Actions.Find(InActionName);

		if (ActionPointsRef > 1)
		{
			ActionPointsRef -= 1;
			Actions.Add(InActionName, ActionPointsRef);


			if (InBRestoreActionPoint)
				Character.ActionPoints += 1;

			Character.CharacterActions = Actions;

			Characters.Add(InCharacterName, Character);
			GI->SetCharacters(Characters);

			RefreshSelectedActionData(InActionName);
			RefreshSelectedCharacterActionsData();
		}
	}
}

void URPGCharactersManagerComponent::ForgetAction(FName InCharacterName, FName InActionName, bool InBRestoreActionPoints)
{
	TMap<FName, FCharacterInfoStruct> Characters = GI->GetCharacters();
	FCharacterInfoStruct Character = *Characters.Find(InCharacterName);
	TMap<FName, int32> Actions = Character.CharacterActions;

	if (Actions.Contains(InActionName))
	{
		int32 ActionPointsRef = *Actions.Find(InActionName);

		Actions.Remove(InActionName);

		Character.CharacterActions = Actions;
		Characters.Add(InCharacterName, Character);
		GI->SetCharacters(Characters);

		if (InBRestoreActionPoints)
			ReceiveActionPoints(InCharacterName, ActionPointsRef - 1);

		RefreshSelectedActionData(InActionName);
	}
}

void URPGCharactersManagerComponent::ReceiveActionPoints(FName InName, int32 InAmount)
{
	TMap<FName, FCharacterInfoStruct> Characters = GI->GetCharacters();
	FCharacterInfoStruct Character = *Characters.Find(InName);

	Character.ActionPoints += InAmount;
	Characters.Add(InName, Character);
	GI->SetCharacters(Characters);

	RefreshSelectedCharacterActionsData();
}

void URPGCharactersManagerComponent::DeductActionPoints(FName InName, int32 InAmount)
{
	TMap<FName, FCharacterInfoStruct> Characters = GI->GetCharacters();
	FCharacterInfoStruct Character = *Characters.Find(InName);

	Character.ActionPoints = FMath::Max(Character.ActionPoints - InAmount, 0);
	Characters.Add(InName, Character);
	GI->SetCharacters(Characters);

	RefreshSelectedCharacterActionsData();
}