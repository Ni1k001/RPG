// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGSavePoint.h"
#include "Engine/CollisionProfile.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "DisplayDebugHelpers.h"

// Sets default values
ARPGSavePoint::ARPGSavePoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SavePointArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Area"));
	SavePointArea->SetBoxExtent(FVector(40.f, 40.f, 40.f));
	SavePointArea->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	SavePointArea->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	SavePointArea->CanCharacterStepUpOn = ECB_No;
	SavePointArea->SetShouldUpdatePhysicsVolume(false);
	SavePointArea->SetCanEverAffectNavigation(false);
	SavePointArea->bDynamicObstacle = true;
	SavePointArea->SetHiddenInGame(true);

	RootComponent = SavePointArea;


	SpawnPointCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SpawnPoint"));
	SpawnPointCapsule->InitCapsuleSize(34.0f, 88.0f);
	SpawnPointCapsule->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	SpawnPointCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SpawnPointCapsule->CanCharacterStepUpOn = ECB_No;
	SpawnPointCapsule->SetShouldUpdatePhysicsVolume(false);
	SpawnPointCapsule->SetCanEverAffectNavigation(false);
	SpawnPointCapsule->bDynamicObstacle = true;
	SpawnPointCapsule->SetHiddenInGame(true);

	SpawnPointCapsule->SetupAttachment(RootComponent);

	ArrowComponent = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	if (ArrowComponent)
	{
		ArrowComponent->ArrowColor = FColor(150, 200, 255);
		ArrowComponent->bTreatAsASprite = true;
		ArrowComponent->SetupAttachment(SpawnPointCapsule);
		ArrowComponent->bIsScreenSizeScaled = true;
	}
}

// Called when the game starts or when spawned
void ARPGSavePoint::BeginPlay()
{
	Super::BeginPlay();
	
}