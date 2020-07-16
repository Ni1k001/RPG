// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "RPG/enums/RPGStatTypeEnum.h"
#include "RPG/enums/RPGActionTypeEnum.h"

#include "RPG/components/RPGBattleManagerComponent.h"

#include "RPG/battle/RPGBattleCharacter.h"

#include "RPG/RPGGameInstance.h"

#include "RPGBattleCharacterStatsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API URPGBattleCharacterStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URPGBattleCharacterStatsComponent(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
		FName Name;

	UPROPERTY()
		FText DisplayName;

	UPROPERTY()
		bool bIsDefending;

	UPROPERTY()
		TMap<StatsEnum, float> Stats;

	UPROPERTY()
		TMap<DerivedStatsEnum, float> DerivedStats;
	
	UPROPERTY()
		float CurrentHP;

	UPROPERTY()
		float CurrentMP;

	UPROPERTY()
		float CurrentInitiative;

	TSubclassOf<class UUserWidget> CharacterBattleSlotClass;

	UPROPERTY()
		class URPGBattleCharacterSlotWidget* BattleCharacterSlotRef;

	UPROPERTY()
		URPGBattleManagerComponent* BattleManagerReference;

	UPROPERTY()
		ActionTypeEnum SelectedActionType;

	UPROPERTY()
		TArray<ARPGBattleCharacter*> TargetedCharacters;

	UPROPERTY()
		URPGGameInstance* GameInstance;

public:
	UFUNCTION()
		FName GetHardcodedName();

	UFUNCTION()
		FText GetDisplayName();

	UFUNCTION()
		bool GetBIsDefending();

	UFUNCTION()
		TMap<StatsEnum, float> GetStats();

	UFUNCTION()
		TMap<DerivedStatsEnum, float> GetDerivedStats();

	UFUNCTION()
		float GetCurrentHP();

	UFUNCTION()
		float GetCurrentMP();

	UFUNCTION()
		float GetCurrentInitiative();

	UFUNCTION()
		class URPGBattleCharacterSlotWidget* GetBattleCharacterSlotRef();

	UFUNCTION()
		void SetBattleCharacterSlotRef(class URPGBattleCharacterSlotWidget* InBattleCharacterSlotRef);

	UFUNCTION()
		URPGBattleManagerComponent* GetBattleManagerRef();

	UFUNCTION()
		void SetBattleManagerRef(URPGBattleManagerComponent* InBattleManagerReference);

	UFUNCTION()
		ActionTypeEnum GetSelectedActionType();

	UFUNCTION()
		void SetSelectedActonType(ActionTypeEnum InSelectedActionType);

	UFUNCTION()
		TArray<ARPGBattleCharacter*> GetTargetedCharacters();

	UFUNCTION()
		void SetTargetedCharacters(TArray<ARPGBattleCharacter*> InTargetedCharacters);

	/*				Initialization				*/
	UFUNCTION()
		void SetCharacterData(FText InDisplayName, TMap<StatsEnum, float> InStats, TMap<DerivedStatsEnum, float> InDerivedStats, float InCurrentHP, float InCurrentMP);

	UFUNCTION()
		void CreateCharacterBattleSlot();

	/*				Damage						*/
	UFUNCTION()
		void ReceiveDamage(float InDamage, float InCriticalRate, float InCriticalPower);

	UFUNCTION()
		float CalculateDefendStanceDamageReduction(float InDamage);

	UFUNCTION()
		void ReduceInitiative(float InAmount);

	UFUNCTION()
		void ReduceHP(float InAmount);

	UFUNCTION()
		void ReduceMP(float InAmount);

	/*				Initiative					*/
	UFUNCTION()
		void RefreshInitiative();

	UFUNCTION()
		void AddInitiative(float InAmount);

	UFUNCTION()
		void RemoveInitiative(float InAmount);

	/*				Recovery					*/
	UFUNCTION()
		void RefreshHP();

	UFUNCTION()
		void RefreshMP();

	UFUNCTION()
		void RecoverHP(float InAmount);

	UFUNCTION()
		void RecoverMP(float InAmount);

	UFUNCTION()
		void Resurrect(float InAmount);
};













































































/*	UFUNCTION()
		FName GetName();

	UFUNCTION()
		void SetName(FName InName);

	UFUNCTION()
		FText GetDisplayName;

	UFUNCTION()
		void SetDisplayName(FText InDisplayName);

	UFUNCTION()
		bool GetIsDefending();

	UFUNCTION()
		void SetIsDefending(bool InBIsDefending);

	UFUNCTION()
		TMap<StatsEnum, float> GetStats();

	UFUNCTION()
		void SetStats(TMap<StatsEnum, float> InStats);

	UFUNCTION()
		TMap<DerivedStatsEnum, float> GetDerivedStats();

	UFUNCTION()
		void SetDerivedStats(TMap<DerivedStatsEnum, float> InDerivedStats);

	UFUNCTION()
		float GetCurrentHP();

	UFUNCTION()
		void SetCurrentHP(float InCurrentHP);

	UFUNCTION()
		float GetCurrentMP();

	UFUNCTION()
		void SetCurrentMP(float InCurrentMP);

	UFUNCTION()
		float GetCurrentInitiative();

	UFUNCTION()
		void SetCurrentInitiative(float InCurrentInitiative);

//	UFUNCTION()
//

//	UFUNCTION()
//

	UFUNCTION()
		URPGBattleManagerComponent* GetBattleManagerReference;

	UFUNCTION()
		void SetBattleManagerReference(URPGBattleManagerComponent* InBattleManagerReference);

	UFUNCTION()
		ActionTypeEnum GetSelectedActionType();

	UFUNCTION()
		void SetSelectedActionType(ActionTypeEnum SelectedActionType);

	UFUNCTION()
		TArray<ARPGBattleCharacter*> GetTargetedCharacters();

	UFUNCTION()
		void SetTargetedCharacters(TArray<ARPGBattleCharacter*> InTargetedCharacters);

	UFUNCTION()
		URPGGameInstance* GetGameInstance();

	UFUNCTION()
		void SetGameInstance(URPGGameInstance* InGameInstance);*/