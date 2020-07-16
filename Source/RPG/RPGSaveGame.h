// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RPG/structs/RPGCharacterInfoStruct.h"
#include "RPG/structs/RPGPartySlotStruct.h"
#include "RPGSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URPGSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	URPGSaveGame();

	/*				DEFAULT				*/
	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		uint32 UserIndex;

	/*				INVENTORY MANAGER				*/
	UPROPERTY(VisibleAnywhere)
		int32 Gold;
	//	INVENTORY - ARRAY OF ITEMS

	/*				CHARACTERS MANAGER				*/
	UPROPERTY(VisibleAnywhere)
		TArray<FPartySlotStruct> Party;

	UPROPERTY(VisibleAnywhere)
		TMap<FName, FCharacterInfoStruct> Characters;

	/*				TIMER				*/
	UPROPERTY(VisibleAnywhere)
		FTimespan TimePlayed;

	/*				MAP INFO				*/
	UPROPERTY(VisibleAnywhere)
		FName WorldMapName;

	UPROPERTY(VisibleAnywhere)
		FName SavePoint;

	/*				World Managment				*/
	UPROPERTY(VisibleAnywhere)
		bool bRandomEncounter;

	UPROPERTY(VisibleAnywhere)
		TMap<FName, bool> InteractedObjects;

	UPROPERTY(VisibleAnywhere)
		TMap<FName, bool> BattledEnemies;
};