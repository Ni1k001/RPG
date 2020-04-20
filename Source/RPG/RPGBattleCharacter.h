// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Character.h"
#include "RPGBattleCharacter.generated.h"

UCLASS()
class RPG_API ARPGBattleCharacter : public ACharacter
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
	UPROPERTY(VisibleAnywhere)
		class UBillboardComponent* Target;

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
};
