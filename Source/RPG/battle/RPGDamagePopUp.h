// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RPGDamagePopUp.generated.h"

UCLASS()
class RPG_API ARPGDamagePopUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARPGDamagePopUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
		class UTextRenderComponent* TextComponent;

	UPROPERTY()
		class UProjectileMovementComponent* ProjectileMovement;

public:
	UPROPERTY()
		float Value;

	UPROPERTY()
		bool bIsCritical;

	UPROPERTY()
		bool bIsHealing;

	UPROPERTY()
		bool bIsRestoringMP;

	UPROPERTY()
		bool bIsReducingInitiative;

	UPROPERTY()
		AActor* CameraReference;

	UFUNCTION()
		void Init();

	/** Returns ProjectileMovement subobject **/
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};
