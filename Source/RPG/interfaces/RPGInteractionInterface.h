// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPG/RPGCharacter.h"
#include "UObject/Interface.h"
#include "RPGInteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URPGInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RPG_API IRPGInteractionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void OnObjectInteractionStateLoaded(bool InteractionState);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void OnEnemyBattleStateLoaded(bool BattleState);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void OnInteractionEnabled();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void OnInteractionDisabled();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void OnInteractionRequested(ARPGCharacter* InteractiongWorldCharacter);
};
