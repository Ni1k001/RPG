// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGMapTeleportPoint.h"
#include "RPG/RPGCharacter.h"
#include "RPG/RPGGameInstance.h"
#include "Engine/CollisionProfile.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
ARPGMapTeleportPoint::ARPGMapTeleportPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TeleportArea = CreateDefaultSubobject<UBoxComponent>(TEXT("TeleportArea"));
	TeleportArea->SetBoxExtent(FVector(40.f, 40.f, 40.f));
	TeleportArea->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	TeleportArea->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	TeleportArea->CanCharacterStepUpOn = ECB_No;
	TeleportArea->SetShouldUpdatePhysicsVolume(false);
	TeleportArea->SetCanEverAffectNavigation(false);
	TeleportArea->bDynamicObstacle = true;
	TeleportArea->SetHiddenInGame(true);

	RootComponent = TeleportArea;

	//TeleportArea->OnComponentBeginOverlap.AddDynamic(this, &ARPGMapTeleportPoint::OnActorBeginOverlap);

	TextComponent = CreateEditorOnlyDefaultSubobject<UTextRenderComponent>(TEXT("Text"));
	if (TextComponent)
	{
		TextComponent->SetupAttachment(TeleportArea);
		TextComponent->SetRelativeLocation(FVector(0.f, 0.f, 120.f));


		TextComponent->Text = FText::FromString("Teleport");

		TextComponent->VerticalAlignment = EVerticalTextAligment::EVRTA_TextCenter;
		TextComponent->HorizontalAlignment = EHorizTextAligment::EHTA_Center;

		TextComponent->TextRenderColor = FColor::White;

		TextComponent->SetHiddenInGame(true);
	}
}

// Called when the game starts or when spawned
void ARPGMapTeleportPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARPGMapTeleportPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARPGMapTeleportPoint::OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnActorBeginOverlap;

	if (OtherActor != NULL && OtherActor->IsA(ARPGCharacter::StaticClass()))
	{
		//TODO
	}
}

FName ARPGMapTeleportPoint::GetDestinationMap()
{
	return DestinationMap;
}

void ARPGMapTeleportPoint::SetDestinationMap(FName InDestinationMap)
{
	DestinationMap = InDestinationMap;
}

FName ARPGMapTeleportPoint::GetDestinationSpawnPoint()
{
	return DestinationSpawnPoint;
}

void ARPGMapTeleportPoint::SetDestinationSpawnPoint(FName InDestinationSpawnPoint)
{
	DestinationSpawnPoint = InDestinationSpawnPoint;
}

FText ARPGMapTeleportPoint::GetDestinationAreaName()
{
	return DestinationAreaName;
}

void ARPGMapTeleportPoint::SetDestinationAreaName(FText InDestinationAreaName)
{
	DestinationAreaName = InDestinationAreaName;
}