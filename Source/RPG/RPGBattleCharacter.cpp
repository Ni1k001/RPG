// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGBattleCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/BillboardComponent.h"
#include "Engine/DataTable.h"
#include "RPGDataTables.h"

// Sets default values
ARPGBattleCharacter::ARPGBattleCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetCapsuleComponent()->OnBeginCursorOver.AddDynamic(this, &ARPGBattleCharacter::OnBeginMouseOver);
	GetCapsuleComponent()->OnEndCursorOver.AddDynamic(this, &ARPGBattleCharacter::OnEndMouseOver);
	GetCapsuleComponent()->OnClicked.AddDynamic(this, &ARPGBattleCharacter::OnClicked);
	GetCapsuleComponent()->OnReleased.AddDynamic(this, &ARPGBattleCharacter::OnReleased);

	Target = CreateDefaultSubobject<UBillboardComponent>(TEXT("TargetPointer"));
	Target->SetRelativeLocation(FVector(0.f, 0.f, 150.f));
	Target->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void ARPGBattleCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARPGBattleCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARPGBattleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARPGBattleCharacter::OnBeginMouseOver(UPrimitiveComponent* TouchedComponent)
{
	Target->SetHiddenInGame(false);
}

void ARPGBattleCharacter::OnEndMouseOver(UPrimitiveComponent* TouchedComponent)
{
	Target->SetHiddenInGame(true);
}

void ARPGBattleCharacter::OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TEXT("OnClicked"));
	}
}

void ARPGBattleCharacter::OnReleased(UPrimitiveComponent* TouchedComponent, FKey ButtonReleased)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TEXT("OnReleased"));
	}
}

/*
FSoftObjectPath DataTableLoader = TEXT("/Game/DataTables/ExperienceDataTable.ExperienceDataTable");
UDataTable* datatable = Cast<UDataTable>(DataTableLoader.TryLoad());

if (datatable)
{
	for (auto& name : datatable->GetRowNames())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *name.ToString());
	}
}
*/