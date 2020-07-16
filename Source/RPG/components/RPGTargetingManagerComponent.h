// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "RPG/enums/RPGTargetingTypeEnum.h"

#include "RPG/battle/RPGBattleCharacter.h"

#include "RPG/RPGGameInstance.h"

#include "RPGTargetingManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API URPGTargetingManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URPGTargetingManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
		bool bIsTargetingEnabled;

	UPROPERTY()
		bool bCanTargetSelf;

	UPROPERTY()
		TargetingTypeEnum SelectedTargetingType;

	UPROPERTY()
		TArray<ARPGBattleCharacter*> TargetedCharacters;

	UPROPERTY()
		URPGGameInstance* GameInstance;

public:
	UFUNCTION()
		bool GetBIsTargetingEnabled();

	UFUNCTION()
		bool GetBCanTargetSelf();

	UFUNCTION()
		TargetingTypeEnum GetSelectedTargetingType();

	UFUNCTION()
		TArray<ARPGBattleCharacter*> GetTargetedCharacters();

	UFUNCTION()
		void EnableTargeting(bool InBCanTargetSelf, TargetingTypeEnum InTargetingType);

	UFUNCTION()
		void DisableTargeting();

	UFUNCTION()
		void ShowTargets(ARPGBattleCharacter* InIndicatedCharacter);

	UFUNCTION()
		void HideTargets();

	UFUNCTION()
		void CancelTargeting();
};
