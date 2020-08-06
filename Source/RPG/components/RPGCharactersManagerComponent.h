// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "RPG/enums/RPGItemTypeEnum.h"
#include "RPG/enums/RPGStatTypeEnum.h"

#include "RPG/structs/RPGCharacterInfoStruct.h"
#include "RPG/structs/RPGPartySlotStruct.h"

#include "RPGCharactersManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API URPGCharactersManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URPGCharactersManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
		int32 MaxCharactersAmountInParty;

	UPROPERTY()
		int32 MaxCharactersAmountInCollection;

	UPROPERTY()
		int32 CharacterMaxLevel;

	UPROPERTY()
		TArray<class URPGCharacterOverviewSlotWidget*> CharacterOverviewSlotsReference;

	UPROPERTY()
		TArray<class URPGCharacterSelectionSlotWidget*> CurrentTeamMembersSlots;

	UPROPERTY()
		TArray<class URPGCharacterSelectionSlotWidget*> OtherMembersSlots;

	UPROPERTY()
		class URPGCharacterOverviewScreenWidget* CharacterOverviewScreenReference;

	UPROPERTY()
		class URPGCharacterSelectScreenWidget* CharacterSelectionScreenReference;

	UPROPERTY()
		FName SelectedCharacter;

	UPROPERTY()
		class URPGCharacterActionsWidget* CharacterActionScreenReference;

	UPROPERTY()
		TArray<class URPGCharacterActionsSlotWidget*> CharacterSlotsInActionScreenReference;

	UPROPERTY()
		TArray<class URPGOwnedActionSlotWidget*> OwnedActionsSlotsReference;

	UPROPERTY()
		FName SelectedAction;

	UPROPERTY()
		class URPGGameInstance* GI;

public:
	UFUNCTION()
		int32 GetMaxCharactersAmountInParty();

	UFUNCTION()
		void SetMaxCharactersAmountInParty(int32 InMaxCharactersAmountInParty);

	UFUNCTION()
		int32 GetMaxCharactersAmountInCollection();

	UFUNCTION()
		void SetMaxCharactersAmountInCollection(int32 InMaxCharactersAmountInCollection);

	UFUNCTION()
		int32 GetCharacterMaxLevel();

	UFUNCTION()
		void SetCharacterMaxLevel(int32 InCharacterMaxLevel);

	UFUNCTION()
		TArray<class URPGCharacterOverviewSlotWidget*> GetCharactersOverviewSlotsReference();

	UFUNCTION()
		void SetCharactersOverviewSlotsReference(TArray<class URPGCharacterOverviewSlotWidget*> InCharacterOverviewSlotsReference);

	UFUNCTION()
		TArray<class URPGCharacterSelectionSlotWidget*> GetCurrentTeamMembersSlots();

	UFUNCTION()
		void SetCurrentTeamMembersSlots(TArray<class URPGCharacterSelectionSlotWidget*> InCurrentTeamMembersSlots);

	UFUNCTION()
		TArray<class URPGCharacterSelectionSlotWidget*> GetOtherMembersSlots();

	UFUNCTION()
		void SetOtherMembersSlots(TArray<class URPGCharacterSelectionSlotWidget*> InOtherMembersSlots);

	UFUNCTION()
		class URPGCharacterOverviewScreenWidget* GetCharacterOverviewScreenReference();

	UFUNCTION()
		void SetCharacterOverviewScreenReference(class URPGCharacterOverviewScreenWidget* InCharacterOverviewScreenReference);

	UFUNCTION()
		class URPGCharacterSelectScreenWidget* GetCharacterSelectionScreenReference();

	UFUNCTION()
		void SetCharacterSelectionScreenReference(class URPGCharacterSelectScreenWidget* InCharacterSelectionScreenReference);

	UFUNCTION()
		FName GetSelectedCharacter();

	UFUNCTION()
		void SetSelectedCharacter(FName InSelectedCharacter);

	UFUNCTION()
		class URPGCharacterActionsWidget* GetCharacterActionScreenReference();

	UFUNCTION()
		void SetCharacterActionScreenReference(class URPGCharacterActionsWidget* InCharacterActionScreenReference);

	UFUNCTION()
		TArray<class URPGCharacterActionsSlotWidget*> GetCharacterSlotsInActionScreenReference();

	UFUNCTION()
		void SetCharacterSlotsInActionScreenReference(TArray<class URPGCharacterActionsSlotWidget*> InCharacterSlotsInActionScreenReference);

	UFUNCTION()
		TArray<class URPGOwnedActionSlotWidget*> GetOwnedActionsSlotsReference();

	UFUNCTION()
		void SetOwnedActionsSlotsReference(TArray<class URPGOwnedActionSlotWidget*> InOwnedActionsSlotsReference);

	UFUNCTION()
		FName GetSelectedAction();

	UFUNCTION()
		void SetSelectedAction(FName InSelectedAction);

	/*				Initialization				*/
	UFUNCTION()
		void CreateReferenceToCharacterOverviewScreen();

	UFUNCTION()
		void CreateReferenceToCharacterSelectonScreen();

	UFUNCTION()
		void CreateReferenceToActionsScreen();

	/*				Party						*/
	UFUNCTION()
		void RefreshCharacterOverviewSlots();

	UFUNCTION()
		void RefreshCharacterSelectionSlots();

	UFUNCTION()
		void AddCharacterToParty(FName InName);

	UFUNCTION()
		void RemoveCharacterFromParty(FName InName);

	UFUNCTION()
		void CheckIfCharacterIsInParty(FName InCharacter, bool& OutBIsSuccess, int32& OutIndex);

	/*				Characters Management		*/
	UFUNCTION()
		void AddNewCharacterToCollection(FCharacterInfoStruct InCharacter);

	UFUNCTION()
		void IncreaseCharacterStats(FName InName, TMap< StatsEnum, float> InStats, TMap< DerivedStatsEnum, float> InDerivedStats);

	UFUNCTION()
		void DecreaseCharacterStats(FName InName, TMap< StatsEnum, float> InStats, TMap< DerivedStatsEnum, float> InDerivedStats);

	UFUNCTION()
		void RestoreHP(FName InName, float InAmount);

	UFUNCTION()
		void RestoreMP(FName InName, float InAmount);

	UFUNCTION()
		void RecoverAllCharacterToFull();

	UFUNCTION()
		void RefreshSelectedCharacterData();

	UFUNCTION()
		void ShowStatsComparison(TMap< StatsEnum, float> InStats, TMap< DerivedStatsEnum, float> InDerivedStats);

	UFUNCTION()
		void HideStatsComparison();

	/*				Leveling					*/
	UFUNCTION()
		void AddExperienceToCharacter(FName InName, int32 InAmount);

	UFUNCTION()
		void LevelUpCharacter(FName InName);

	/*				Actions						*/
	UFUNCTION()
		void RefreshCharactersSlotsInActionScreen();

	UFUNCTION()
		void RefreshSelectedCharacterActionsData();

	UFUNCTION()
		class URPGOwnedActionSlotWidget* GetProperActionSlot(int32 InIndex);

	UFUNCTION()
		void RefreshSelectedActionData(FName InName);

	UFUNCTION()
		void LearnNewAction(FName InCharacterName, FName InActionName, bool InBUpdateIfIsAlreadyLearned);

	UFUNCTION()
		void UpgradeAction(FName InCharacterName, FName InActionName);

	UFUNCTION()
		void DegradeAction(FName InCharacterName, FName InActionName, bool InBRestoreActionPoint);

	UFUNCTION()
		void ForgetAction(FName InCharacterName, FName InActionName, bool InBRestoreActionPoints);

	UFUNCTION()
		void ReceiveActionPoints(FName InName, int32 InAmount);

	UFUNCTION()
		void DeductActionPoints(FName InName, int32 InAmount);
};
