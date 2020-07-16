// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RPGMapTeleportPoint.generated.h"

UCLASS()
class RPG_API ARPGMapTeleportPoint : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARPGMapTeleportPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* TeleportArea;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UTextRenderComponent* TextComponent;

	UPROPERTY(BlueprintGetter = GetDestinationMap, BlueprintSetter = SetDestinationMap, VisibleAnywhere)
		FName DestinationMap;

	UPROPERTY(BlueprintGetter = GetDestinationSpawnPoint, BlueprintSetter = SetDestinationSpawnPoint, VisibleAnywhere)
		FName DestinationSpawnPoint;

	UPROPERTY(BlueprintGetter = GetDestinationAreaName, BlueprintSetter = SetDestinationAreaName, VisibleAnywhere)
		FText DestinationAreaName;

public:
	UFUNCTION(BlueprintCallable)
		void OnActorBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintGetter, Category = "Teleport")
		FName GetDestinationMap();

	UFUNCTION(BlueprintSetter, Category = "Teleport")
		void SetDestinationMap(FName InDestinationMap);

	UFUNCTION(BlueprintGetter, Category = "Teleport")
		FName GetDestinationSpawnPoint();

	UFUNCTION(BlueprintSetter, Category = "Teleport")
		void SetDestinationSpawnPoint(FName InDestinationSpawnPoint);

	UFUNCTION(BlueprintGetter, Category = "Teleport")
		FText GetDestinationAreaName();

	UFUNCTION(BlueprintSetter, Category = "Teleport")
		void SetDestinationAreaName(FText InDestinationAreaName);
};
