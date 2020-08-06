// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Character.h"

#include "RPG/enums/RPGActionTypeEnum.h"

#include "RPG/interfaces/RPGAnimCommunicationInterface.h"
#include "RPG/interfaces/RPGBattleCommunicationInterface.h"

#include "RPGBattleCharacter.generated.h"

UCLASS()
class RPG_API ARPGBattleCharacter : public ACharacter, public IRPGBattleCommunicationInterface, public IRPGAnimCommunicationInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARPGBattleCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
//	UPROPERTY()
//		

	UPROPERTY(VisibleAnywhere)
		class UBillboardComponent* Target;

	UPROPERTY()
		class URPGBattleCharacterStatsComponent* CharacterStats;

	UPROPERTY()
		class URPGBattleManagerComponent* BattleManagerRef;

	UPROPERTY()
		class URPGTargetingManagerComponent* TargetingManagerRef;

	UPROPERTY()
		bool bIsControlledByAI;

	UPROPERTY()
		bool bIsDead;

	UPROPERTY()
		TArray<ARPGBattleCharacter*> TargetedCharacters;

	UPROPERTY()
		bool bIsEnemy;

	void TestFunc();

//	UPROPERTY(VisibleAnywhere)

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void OnBeginMouseOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
		void OnEndMouseOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
		void OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed = EKeys::LeftMouseButton);

	UFUNCTION()
		void OnReleased(UPrimitiveComponent* TouchedComponent, FKey ButtonReleased = EKeys::LeftMouseButton);

	//Default
	UFUNCTION()
		class UBillboardComponent* GetTarget();

	UFUNCTION()
		class URPGBattleCharacterStatsComponent* GetCharacterStats();

	UFUNCTION()
		void SetCharacterStats(class URPGBattleCharacterStatsComponent* InCharacterStats);

	UFUNCTION()
		class URPGBattleManagerComponent* GetBattleManager();

	UFUNCTION()
		void SetBattleManager(class URPGBattleManagerComponent* InBattleManagerRef);

	UFUNCTION()
		class URPGTargetingManagerComponent* GetTargetingManager();

	UFUNCTION()
		void SetTargetingManager(class URPGTargetingManagerComponent* InTargetingManagerRef);

	UFUNCTION()
		bool GetBIsControlledByAI();

	UFUNCTION()
		void SetBIsControlledByAI(bool InBIsControlledByAI);

	UFUNCTION()
		bool GetBIsDead();

	UFUNCTION()
		void SetBIsDead(bool InBIsDead);

	UFUNCTION()
		TArray<ARPGBattleCharacter*> GetTargetedCharacters();

	UFUNCTION()
		void SetTargetedCharacters(TArray<ARPGBattleCharacter*> InTargetedCharacters);

	UFUNCTION()
		bool GetBIsEnemy();

	UFUNCTION()
		void SetBIsEnemy(bool InBIsEnemy);

	//Interface
	void OnDamageReceived_Implementation(float Damage, bool bIsCritical) override;
	void OnDeath_Implementation();
	void OnHealed_Implementation(float HealAmmount, bool bIsMPRestored);
	void OnInitiativeReduced_Implementation(float ReductionAmmount);
	void OnResurrected_Implementation(float HealAmmount);

	//Action
	void ExecuteAction(ActionTypeEnum InActionType, FName InSecondaryActionName);
	void ExecuteAttackAction();
	void ExecuteDefendAction();
	void ExecuteItemAction(FName InItemName);
	void ExecuteMagicAction(FName InMagicName);
	void ExecuteFleeAction();
};
