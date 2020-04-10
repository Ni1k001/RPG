// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RPGCharacterInfoStruct.h"
#include "RPGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URPGGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	/*				DEFAULT				*/
	FTimespan* StartTime;

	/*				INVENTORY MANAGER				*/
	UPROPERTY(BlueprintGetter = GetGold, BlueprintSetter = SetGold, Category = "InventoryManager")
		int32 Gold;

	//UPROPERTY(VisibleAnywhere)
	//	INVENTORY - ARRAY OF ITEMS

	/*				CHARACTERS MANAGER				*/
	UPROPERTY(BlueprintGetter = GetParty, BlueprintSetter = SetParty, Category = "CharacterManager")
		TArray<FCharacterInfoStruct> Party;

	UPROPERTY(BlueprintGetter = GetCharacters, BlueprintSetter = SetCharacters, Category = "CharacterManager")
		TMap<FName, FCharacterInfoStruct> Characters;

	/*				TIMER				*/
	FTimespan* TimePlayed;

	/*				MAP INFO				*/
	UPROPERTY(BlueprintGetter = GetWorldMapName,BlueprintSetter = SetWorldMapName, Category = "MapInfo")
		FName WorldMapName;

	UPROPERTY(BlueprintGetter = GetWorldTransformBeforeBattle, BlueprintSetter = SetWorldTransformBeforeBattle, Category = "MapInfo")
		FTransform WorldTransformBeforeBattle;

	UPROPERTY(BlueprintGetter = GetCameraRotationBeforeBattle, BlueprintSetter = SetCameraRotationBeforeBattle, Category = "MapInfo")
		FRotator CameraRotationBeforeBattle;

	UPROPERTY(BlueprintGetter = GetEnemiesTransformsBeforeBattle, BlueprintSetter = SetEnemiesTransformsBeforeBattle, Category = "MapInfo")
		TMap<FName, FTransform> EnemiesTransformsBeforeBattle;

	/*				ENCOUNTERS				*/
	UPROPERTY(BlueprintGetter = GetPossibleEncounters, BlueprintSetter = SetPossibleEncounters, Category = "Encounters")
		TArray<FName> PossibleEncounters;
	
	UPROPERTY(BlueprintGetter = GetPossibleBattleMaps, BlueprintSetter = SetPossibleBattleMaps, Category = "Encounters")
		TArray<FName> PossibleBattleMaps;
	
	UPROPERTY(BlueprintGetter = GetRandomEncounter, BlueprintSetter = SetRandomEncounter, Category = "Encounters")
		bool bRandomEncounter;
	
	UPROPERTY(BlueprintGetter = GetEncounteredEnemies, BlueprintSetter = SetEncounteredEnemies, Category = "Encounters")
		TMap<int32, FName> EncounteredEnemies;

	/*				World Managment				*/
	UPROPERTY(BlueprintGetter = GetInteractedObjects, BlueprintSetter = SetInteractedObjects, Category = "WorldManagment")
		TMap<FName, bool> InteractedObjects;
	
	UPROPERTY(BlueprintGetter = GetBattledEnemies, BlueprintSetter = SetBattledEnemies, Category = "WorldManagment")
		TMap<FName, bool> BattledEnemies;

protected:


public:
	/*				DEFAULT				*/
	virtual void Init() override;
	virtual void OnStart() override;
	virtual void Shutdown() override;

	UFUNCTION(BlueprintCallable)
		static FString GetAppVersion();

	/*				SAVED DATA				*/
	UFUNCTION(BlueprintCallable)
		void SaveData(FString SaveSlotName, int32 UserIndex, FName SavePoint);

	UFUNCTION(BlueprintCallable)
		void LoadData(FString SaveSlotName, int32 UserIndex, FName& SavePoint);

	/*				INVENTORY MANAGER				*/
	UFUNCTION(BlueprintGetter, Category = "InventoryManager")
		int32 GetGold();

	UFUNCTION(BlueprintSetter, Category = "InventoryManager")
		void SetGold(int32 InGold);

	//UFUNCTION
	//UFUNCTION

	/*				CHARACTERS MANAGER				*/
	UFUNCTION(BlueprintGetter, Category = "CharacterManager")
		TArray<FCharacterInfoStruct> GetParty();

	UFUNCTION(BlueprintSetter, Category = "CharacterManager")
		void SetParty(TArray<FCharacterInfoStruct> InParty);

	UFUNCTION(BlueprintCallable, Category = "CharacterManager")
		void ChangePartyMember(int32 Index, FCharacterInfoStruct Character);

	UFUNCTION(BlueprintGetter, Category = "CharacterManager")
		TMap<FName, FCharacterInfoStruct> GetCharacters();

	UFUNCTION(BlueprintSetter, Category = "CharacterManager")
		void SetCharacters(TMap<FName, FCharacterInfoStruct> InCharacters);

	UFUNCTION(BlueprintCallable, Category = "CharacterManager")
		void SetCharacter(FCharacterInfoStruct Character, int32 Index);

	/*				TIMER				*/
	FTimespan* GetTimePlayed();

	void SetTimePlayed(FTimespan* InTimePlayed);

	void AddTimePlayed(FTimespan* InTimePlayed);

	UFUNCTION(BlueprintCallable)
		void UpdateTimePlayed();

	/*				MAP INFO				*/
	UFUNCTION(BlueprintGetter, Category = "MapInfo")
		FName GetWorldMapName();

	UFUNCTION(BlueprintSetter, Category = "MapInfo")
		void SetWorldMapName(FName InWorldMapName);

	UFUNCTION(BlueprintGetter, Category = "MapInfo")
		FTransform GetWorldTransformBeforeBattle();

	UFUNCTION(BlueprintSetter, Category = "MapInfo")
		void SetWorldTransformBeforeBattle(FTransform InWorldTransformBeforeBattle);

	UFUNCTION(BlueprintGetter, Category = "MapInfo")
		FRotator GetCameraRotationBeforeBattle();

	UFUNCTION(BlueprintSetter, Category = "MapInfo")
		void SetCameraRotationBeforeBattle(FRotator InCameraRotationBeforeBattle);

	UFUNCTION(BlueprintGetter, Category = "MapInfo")
		TMap<FName, FTransform> GetEnemiesTransformsBeforeBattle();

	UFUNCTION(BlueprintSetter, Category = "MapInfo")
		void SetEnemiesTransformsBeforeBattle(TMap<FName, FTransform> InEnemiesTransformsBeforeBattle);

	/*				ENCOUNTERS				*/
	UFUNCTION(BlueprintGetter, Category = "Encounters")
		TArray<FName> GetPossibleEncounters();

	UFUNCTION(BlueprintSetter, Category = "Encounters")
		void SetPossibleEncounters(TArray<FName> InPossibleEncounters);
	
	UFUNCTION(BlueprintGetter, Category = "Encounters")
		TArray<FName> GetPossibleBattleMaps();

	UFUNCTION(BlueprintSetter, Category = "Encounters")
		void SetPossibleBattleMaps(TArray<FName> InPossibleBattleMaps);
	
	UFUNCTION(BlueprintGetter, Category = "Encounters")
		bool GetRandomEncounter();
	
	UFUNCTION(BlueprintSetter, Category = "Encounters")
		void SetRandomEncounter(bool InbRandomEncounter);

	UFUNCTION(BlueprintGetter, Category = "Encounters")
		TMap<int32, FName> GetEncounteredEnemies();

	UFUNCTION(BlueprintSetter, Category = "Encounters")
		void SetEncounteredEnemies(TMap<int32, FName> InEncounteredEnemies);

	/*				World Managment				*/
	UFUNCTION(BlueprintGetter, Category = "WorldManagment")
		TMap<FName, bool> GetInteractedObjects();

	UFUNCTION(BlueprintSetter, Category = "WorldManagment")
		void SetInteractedObjects(TMap<FName, bool> InInteractedObject);

	UFUNCTION(BlueprintGetter, Category = "WorldManagment")
		TMap<FName, bool> GetBattledEnemies();

	UFUNCTION(BlueprintSetter, Category = "WorldManagment")
		void SetBattledEnemies(TMap<FName, bool> InBattledEnemies);
};