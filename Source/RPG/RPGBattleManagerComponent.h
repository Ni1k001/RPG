// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGCharacter.h"
#include "Components/ActorComponent.h"
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
		ACharacter* CurrentCharacter; //Change to BattleCharacterBase

	UPROPERTY(BlueprintGetter = GetPlayerCharacters, BlueprintSetter = SetPlayerCharacters, Category = "Default")
		TArray<ARPGCharacter*> PlayerCharacters; //Change to BattleCharacterBase

	UPROPERTY(BlueprintGetter = GetEnemyCharacters, BlueprintSetter = SetEnemyCharacters, Category = "Default")
		TArray<ACharacter*> EnemyCharacters; //Change to BattleCharacterBase

	//TODO
	//Action

public:
	/*				DEFAULT				*/
	UFUNCTION(BlueprintGetter, Category = "Default")
		float GetRequiredInitiative();

	UFUNCTION(BlueprintSetter, Category = "Default")
		void SetRequiredInitiative(float InRequiredInitiative);

	UFUNCTION(BlueprintGetter, Category = "Default")
		ACharacter* GetCurrentCharacter(); //Change to BattleCharacterBase

	UFUNCTION(BlueprintSetter, Category = "Default")
		void SetCurrentCharacter(ACharacter* InCharacter); //Change to BattleCharacterBase

	UFUNCTION(BlueprintGetter, Category = "Default")
		TArray<ARPGCharacter*> GetPlayerCharacters(); //Change to BattleCharacterBase

	UFUNCTION(BlueprintSetter, Category = "Default")
		void SetPlayerCharacters(TArray<ARPGCharacter*> InPlayerCharacters); //Change to BattleCharacterBase

	UFUNCTION(BlueprintGetter, Category = "Default")
		TArray<ACharacter*> GetEnemyCharacters(); //Change to BattleCharacter

	UFUNCTION(BlueprintSetter, Category = "Default")
		void SetEnemyCharacters(TArray<ACharacter*> InEnemyCharacters); //Change to BattleCharacterBase

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
		void GetCharacterWithMaxInitiative(bool& OutSuccess, ACharacter*& OutCharacter); //Change to BattleCharacterBase

	UFUNCTION()
		void StartCharacterTurn(ACharacter* Character); //Change to BattleCharacterBase

	UFUNCTION()
		void EndCharacterTurn();

	/*				BATTLE END				*/
	UFUNCTION(BlueprintCallable)
		void ReturnToWorldMap();
};
