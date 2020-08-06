// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraActor.h"
#include "RPGDynamicCameraManagerComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API URPGDynamicCameraManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URPGDynamicCameraManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
		FName DefaultPathID;
	
	UPROPERTY()
		bool bUseAutoCameraManagement;

	UPROPERTY()
		ACameraActor* Camera;

	UPROPERTY()
		TMap<FName, class ARPGDynamicCameraPath*> DynamicCameraPaths;

	UPROPERTY()
		class ARPGDynamicCameraPath* ActiveCameraPath;

	UPROPERTY()
		float PathDistance;

	UPROPERTY()
		float Speed;

	UPROPERTY()
		bool bIsLoopEnabled;

public:
	UFUNCTION()
		void SetNewDynamicPath(FName InPathID, bool InBRandomStartDistance, bool InBLoop, bool InBUpdatePathLocation, FVector InNewLocation);

	UFUNCTION()
		void UpdateCameraLocationAndRotation(float InPathTime);

};
