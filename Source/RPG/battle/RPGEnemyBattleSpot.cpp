// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGEnemyBattleSpot.h"
#include "Engine/CollisionProfile.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/TextRenderComponent.h"


// Sets default values
ARPGEnemyBattleSpot::ARPGEnemyBattleSpot()
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
		ArrowComponent->bTreatAsASprite = true;
		ArrowComponent->SetupAttachment(SpawnPointCapsule);
		ArrowComponent->bIsScreenSizeScaled = true;
	}

	TextComponent = CreateEditorOnlyDefaultSubobject<UTextRenderComponent>(TEXT("Text"));
	if (TextComponent)
	{
		TextComponent->SetupAttachment(SpawnPointCapsule);
		TextComponent->SetRelativeLocation(FVector(0, 0, 120));


		TextComponent->Text = FText::FromString("EnemySpot");

		TextComponent->VerticalAlignment = EVerticalTextAligment::EVRTA_TextCenter;
		TextComponent->HorizontalAlignment = EHorizTextAligment::EHTA_Center;

		TextComponent->TextRenderColor = FColor::Red;
	}
}

// Called when the game starts or when spawned
void ARPGEnemyBattleSpot::BeginPlay()
{
	Super::BeginPlay();
	
}

int32 ARPGEnemyBattleSpot::GetSlotIndex()
{
	return SlotIndex;
}

void ARPGEnemyBattleSpot::SetSlotIndex(int32 InSlotIndex)
{
	SlotIndex = InSlotIndex;
}

UArrowComponent* ARPGEnemyBattleSpot::GetArrowComponent()
{
	return ArrowComponent;
}