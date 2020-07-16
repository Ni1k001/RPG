// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Camera/CameraComponent.h"
#include "RPG/enums/RPGPathTypeEnum.h"
#include "RPGDynamicCameraPath.generated.h"

UCLASS()
class RPG_API ARPGDynamicCameraPath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARPGDynamicCameraPath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
		USplineComponent* SplineComponent;

	UPROPERTY()
		UCameraComponent* Camera;

	UPROPERTY()
		FName PathID;

	UPROPERTY()
		PathTypeEnum PathType;

	UPROPERTY()
		int32 PointsAmount;

	UPROPERTY()
		FVector CameraFocusPoint;

	UPROPERTY()
		FRotator PathInitialRotation;

	UPROPERTY()
		float LoopRadius;

	UPROPERTY()
		bool bIsLoopClosed;

	UPROPERTY()
		float SpiralRadius;

	UPROPERTY()
		float SpiralLength;

	UPROPERTY()
		float SpiralOffset;

	UPROPERTY()
		float PreviewTime;

public:
	UFUNCTION()
		USplineComponent* GetSpline();

	UFUNCTION()
		FName GetPathID();

	UFUNCTION()
		PathTypeEnum GetPathType();

	UFUNCTION()
		FVector GetCameraFoucsPoint();

	UFUNCTION()
		FRotator GetPathInitialRotation();

	UFUNCTION()
		float GetLoopRadius();

	UFUNCTION()
		bool GetBIsLoopClosed();

	UFUNCTION()
		float GetSpiralRadius();

	UFUNCTION()
		float GetSpiralLength();

	UFUNCTION()
		float GetSpiralOffset();

	UFUNCTION()
		float GetPreviewTime();

	UFUNCTION()
		FVector GetPathLocationAtDistance(float Time);

	UFUNCTION()
		FVector GetCameraFocusPoint();
};
