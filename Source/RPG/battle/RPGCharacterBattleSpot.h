// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RPGCharacterBattleSpot.generated.h"

UCLASS()
class RPG_API ARPGCharacterBattleSpot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARPGCharacterBattleSpot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent* SpawnPointCapsule;

	UPROPERTY()
		class UArrowComponent* ArrowComponent;

	UPROPERTY()
		class UTextRenderComponent* TextComponent;

	UPROPERTY(BlueprintGetter = GetSlotIndex, BlueprintSetter = SetSlotIndex)
		int32 SlotIndex;

public:
	UFUNCTION(BlueprintGetter)
		int32 GetSlotIndex();

	UFUNCTION(BlueprintSetter)
		void SetSlotIndex(int32 InSlotIndex);

	UFUNCTION()
		UArrowComponent* GetArrowComponent();
};