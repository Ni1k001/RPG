// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "RPG/enums/RPGActionTypeEnum.h"

#include "RPG/structs/RPGItemDataStruct.h"

#include "RPGBattleManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API URPGBattleManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URPGBattleManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(BlueprintGetter = GetRequiredInitiative, BlueprintSetter = SetRequiredInitiative, Category = "Default")
		float RequiredInitiative;

	//BattleEndScreenRef

	//BattleInterfaceRef

	//BattleEndCharacterSlotsRef

	//SecondaryActionSlotsRef

	UPROPERTY(BlueprintGetter = GetCurrentCharacter, BlueprintSetter = SetCurrentCharacter, Category = "Default")
		class ARPGBattleCharacter* CurrentCharacter;

	UPROPERTY(BlueprintGetter = GetPlayerCharacters, BlueprintSetter = SetPlayerCharacters, Category = "Default")
		TArray<class ARPGBattleCharacter*> PlayerCharacters;

	UPROPERTY(BlueprintGetter = GetEnemyCharacters, BlueprintSetter = SetEnemyCharacters, Category = "Default")
		TArray<class ARPGBattleCharacter*> EnemyCharacters;

	UPROPERTY()
		TArray<class ARPGBattleCharacter*> DeadPlayerCharacters;

	UPROPERTY()
		TArray<class ARPGBattleCharacter*> DeadEnemyCharacters;

	UPROPERTY()
		ActionTypeEnum SelectedAction;

	UPROPERTY()
		FName SelectedSecondaryAction;

public:
	/*				DEFAULT				*/
	UFUNCTION(BlueprintGetter, Category = "Default")
		float GetRequiredInitiative();

	UFUNCTION(BlueprintSetter, Category = "Default")
		void SetRequiredInitiative(float InRequiredInitiative);

	//

	UFUNCTION(BlueprintGetter, Category = "Default")
		class ARPGBattleCharacter* GetCurrentCharacter();

	UFUNCTION(BlueprintSetter, Category = "Default")
		void SetCurrentCharacter(class ARPGBattleCharacter* InCharacter);

	UFUNCTION(BlueprintGetter, Category = "Default")
		TArray<class ARPGBattleCharacter*> GetPlayerCharacters();

	UFUNCTION(BlueprintSetter, Category = "Default")
		void SetPlayerCharacters(TArray<class ARPGBattleCharacter*> InPlayerCharacters);

	UFUNCTION(BlueprintGetter, Category = "Default")
		TArray<class ARPGBattleCharacter*> GetEnemyCharacters();

	UFUNCTION(BlueprintSetter, Category = "Default")
		void SetEnemyCharacters(TArray<class ARPGBattleCharacter*> InEnemyCharacters);

	UFUNCTION()
		TArray<class ARPGBattleCharacter*> GetDeadPlayerCharacters();

	UFUNCTION()
		void SetDeadPlayerCharacters(TArray<class ARPGBattleCharacter*> InDeadPlayerCharacters);

	UFUNCTION()
		TArray<class ARPGBattleCharacter*> GetDeadEnemyCharacters();

	UFUNCTION()
		void SetDeadEnemyCharacters(TArray<class ARPGBattleCharacter*> InDeadEnemyCharacters);

	UFUNCTION()
		ActionTypeEnum GetSelectedAction();

	UFUNCTION()
		void SetSelectedAction(ActionTypeEnum InSelectedAction);

	UFUNCTION()
		FName GetSelectedSecondaryAction();

	UFUNCTION()
		void SetSelectedSecondaryAction(FName InSelectedSecondaryAction);

	/*				PRE BATTLE				*/
	UFUNCTION(BlueprintCallable)
		void EncounteredEnemies(FName InEncounterName, FName InBattleMapName);

	UFUNCTION()
		void OpenBattleMap(FName InBattleMapName, TMap<int32, FName> InEncounteredEnemies);

	UFUNCTION()
		TMap<FName, FTransform> GetWorldEnemiesTransforms();

	/*				BATTLE INITIALIZATION				*/
	UFUNCTION()
		void SpawnPlayerTeam();

	UFUNCTION()
		void SpawnEnemyTeam();

	UFUNCTION()
		FTransform GetBattleSpawnPointTransform(bool bEnemySpot, int32 SpotIndex);

	/*				BATTLE IN PROGRESS				*/
	UFUNCTION(BlueprintCallable)
		void GetCharacterWithMaxInitiative(bool& OutSuccess, class ARPGBattleCharacter*& OutCharacter);

	UFUNCTION()
		void StartCharacterTurn(class ARPGBattleCharacter* InCharacter);

	UFUNCTION()
		void SelectAction(ActionTypeEnum InActionType);

	UFUNCTION()
		void RequestActionExecution(TArray<class ARPGBattleCharacter*> InTargetedCharacters);

	UFUNCTION()
		void SelectSecondaryAction(FName InSelectedSecondaryAction);

	UFUNCTION()
		void DisableTargetingAndInput();

	UFUNCTION()
		void OnEnemyKilled(class ARPGBattleCharacter* InEnemy);

	UFUNCTION()
		void OnPlayerCharacterKilled(class ARPGBattleCharacter* InPlayerCharacter);

	UFUNCTION()
		void OnPlayerCharacterResurrected(class ARPGBattleCharacter* InPlayerCharacter);

	UFUNCTION()
		TArray<FItemDataStruct> GetAllItemsUsableInBattle(TArray<FItemDataStruct> InInventory);

	UFUNCTION()
		void EndCharacterTurn(float InUsedInitiative);

	UFUNCTION()
		void ShowActionWidget();

	UFUNCTION()
		void HideActionWidget();

	UFUNCTION()
		void ShowBattleTooltip(FText InTooltipText);

//	UFUNCTION()
//		 GetProperSecondaryActionSlotWidget(int32 InSlotIndex);

	/*				BATTLE END				*/
	UFUNCTION(BlueprintCallable)
		void ReturnToWorldMap();

	UFUNCTION()
		void RollBattleRewards(int32& OutExperience, int32& OutGold, TArray<FItemDataStruct>& OutItemsLooted);

	UFUNCTION()
		void CheckIfAlreadyLootedItem(FName InItemName, TArray<FItemDataStruct> InLootedItems, bool& OutBIsAlreadyLooted, int32& OutSlotIndex);

	UFUNCTION()
		void ReceiveBattleRewards(int32 InExperience, int32 InGold, TArray<FItemDataStruct> InItemsLooted);

	UFUNCTION()
		void ShowBattleEndScreen();

	UFUNCTION()
		void CreateBattleInterface();

	UFUNCTION()
		void UpdateBattleEndScreenOnClick();

	/*				BATTLE					*/
	UFUNCTION()
		void ResumeBattle();

	UFUNCTION()
		void AddInitiativeToAllCharacters();

	UFUNCTION()
		void EndBattle();

	UFUNCTION()
		void GameOver();
};