// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "RPG/RPGCharacter.h"

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

	UPROPERTY(BlueprintGetter = GetCurrentCharacter, BlueprintSetter = SetCurrentCharacter, Category = "Default")
		class ARPGBattleCharacter* CurrentCharacter;

	UPROPERTY(BlueprintGetter = GetPlayerCharacters, BlueprintSetter = SetPlayerCharacters, Category = "Default")
		TArray<ARPGBattleCharacter*> PlayerCharacters;

	UPROPERTY(BlueprintGetter = GetEnemyCharacters, BlueprintSetter = SetEnemyCharacters, Category = "Default")
		TArray<ARPGBattleCharacter*> EnemyCharacters;

	UPROPERTY()
		TArray<ARPGBattleCharacter*> DeadPlayerCharacters;

	UPROPERTY()
		TArray<ARPGBattleCharacter*> DeadEnemyCharacters;

	//TODO
	//Action

public:
	/*				DEFAULT				*/
	UFUNCTION(BlueprintGetter, Category = "Default")
		float GetRequiredInitiative();

	UFUNCTION(BlueprintSetter, Category = "Default")
		void SetRequiredInitiative(float InRequiredInitiative);

	UFUNCTION(BlueprintGetter, Category = "Default")
		ARPGBattleCharacter* GetCurrentCharacter();

	UFUNCTION(BlueprintSetter, Category = "Default")
		void SetCurrentCharacter(ARPGBattleCharacter* InCharacter);

	UFUNCTION(BlueprintGetter, Category = "Default")
		TArray<ARPGBattleCharacter*> GetPlayerCharacters();

	UFUNCTION(BlueprintSetter, Category = "Default")
		void SetPlayerCharacters(TArray<ARPGBattleCharacter*> InPlayerCharacters);

	UFUNCTION(BlueprintGetter, Category = "Default")
		TArray<ARPGBattleCharacter*> GetEnemyCharacters();

	UFUNCTION(BlueprintSetter, Category = "Default")
		void SetEnemyCharacters(TArray<ARPGBattleCharacter*> InEnemyCharacters);

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
		void GetCharacterWithMaxInitiative(bool& OutSuccess, ARPGBattleCharacter*& OutCharacter);

	UFUNCTION()
		void StartCharacterTurn(ARPGBattleCharacter* InCharacter);

	UFUNCTION()
		void SelectAction(ActionTypeEnum InActionType);

	UFUNCTION()
		void RequestActionExecution(TArray<ARPGBattleCharacter*> InTargetedCharacters);

	UFUNCTION()
		void SelectSecondaryAction(FName InSelectedSecondaryAction);

	UFUNCTION()
		void DisableTargetingAndInput(ARPGBattleCharacter* InEnemy);

	UFUNCTION()
		void OnEnemyKilled(ARPGBattleCharacter* InEnemy);

	UFUNCTION()
		void OnPlayerCharacterKilled(ARPGBattleCharacter* InPlayerCharacter);

	UFUNCTION()
		void OnPlayerCharacterResurrected(ARPGBattleCharacter* InPlayerCharacter);

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
		void RollBattleRewards();

	UFUNCTION()
		void CheckIfAlreadyLootedItem();

	UFUNCTION()
		void ReceiveBattleRewards();

	UFUNCTION()
		void ShowBattleEndScreen();

	UFUNCTION()
		void CreateBattleInterface();

	UFUNCTION()
		void UpdateBattleEndScreenOnClick();
};
