// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RPG/RPGGameInstance.h"
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

//	UPROPERTY()
//		TArray<UUserWidget*> 

//	UPROPERTY()
//		TArray<

//	UPROPERTY()
//		TArray<

//	UPROPERTY()
//		?

//	UPROPERTY()
//		?

	UPROPERTY()
		FName SelectedCharacter;

//	UPROPERTY()
//		?

//	UPROPERTY()
//		TArray<

//	UPROPERTY()
//		TArray<

	UPROPERTY()
		FName SelectedAction;

	UPROPERTY()
		URPGGameInstance* GameInstance;

public:
	/*				Initialization				*/

	/*				Party						*/

	/*				Characters Management		*/

	/*				Leveling					*/

	/*				Actions						*/
};
