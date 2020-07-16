// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGSpawnPoint.h"
#include "Engine/CollisionProfile.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
ARPGSpawnPoint::ARPGSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
		ArrowComponent->bTreatAsASprite = false;
		ArrowComponent->SetupAttachment(SpawnPointCapsule);
		ArrowComponent->bIsScreenSizeScaled = false;
		ArrowComponent->bUseInEditorScaling = true;
	}

	TextComponent = CreateEditorOnlyDefaultSubobject<UTextRenderComponent>(TEXT("Text"));
	if (TextComponent)
	{
		TextComponent->SetupAttachment(SpawnPointCapsule);
		TextComponent->SetRelativeLocation(FVector(0.f, 0.f, 120.f));


		TextComponent->Text = FText::FromString("Spawn Point");

		TextComponent->VerticalAlignment = EVerticalTextAligment::EVRTA_TextCenter;
		TextComponent->HorizontalAlignment = EHorizTextAligment::EHTA_Center;

		TextComponent->TextRenderColor = FColor::Green;

		TextComponent->SetHiddenInGame(true);
	}
}

// Called when the game starts or when spawned
void ARPGSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

FTransform ARPGSpawnPoint::GetSpawnTransform()
{
	return ArrowComponent->GetComponentTransform();
}