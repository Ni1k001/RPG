// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGBattleCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/BillboardComponent.h"
#include "Engine/DataTable.h"

#include "RPG/RPGDataTables.h"
#include "RPG/RPGGameInstance.h"

#include "RPG/battle/RPGDamagePopUp.h"

#include "RPG/components/RPGBattleManagerComponent.h"
#include "RPG/components/RPGTargetingManagerComponent.h"
#include "RPG/components/RPGBattleCharacterStatsComponent.h"

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
	Target->SetupAttachment(RootComponent);
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
	if (TargetingManagerRef->IsValidLowLevel())
	{
		if (TargetingManagerRef->GetBIsTargetingEnabled())
		{
			TargetingManagerRef->ShowTargets(this);
		}
	}
//	Target->SetHiddenInGame(false);
}

void ARPGBattleCharacter::OnEndMouseOver(UPrimitiveComponent* TouchedComponent)
{
	if (TargetingManagerRef->IsValidLowLevel())
	{
		if (TargetingManagerRef->GetBIsTargetingEnabled())
		{
			TargetingManagerRef->HideTargets();
		}
	}
//	Target->SetHiddenInGame(true);
}

void ARPGBattleCharacter::OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TEXT("OnClicked"));
	}
	
	URPGGameInstance* GI = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());

	UE_LOG(LogTemp, Warning, TEXT("TEST"));

	if (TargetingManagerRef->IsValidLowLevel())
	{
		if (TargetingManagerRef->GetBIsTargetingEnabled())
		{
			if (TargetingManagerRef->GetTargetedCharacters().Contains(this))
			{
				if (BattleManagerRef->IsValidLowLevel())
				{
					//
				}
			}
		}
	}

	//OnDamageReceived_Implementation(5, true);
	//OnHealed_Implementation(5, false);
	//OnInitiativeReduced_Implementation(5);
	//OnResurrected_Implementation(5);
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

UBillboardComponent* ARPGBattleCharacter::GetTarget()
{
	return Target;
}

URPGBattleCharacterStatsComponent* ARPGBattleCharacter::GetCharacterStats()
{
	return CharacterStats;
}


void ARPGBattleCharacter::SetCharacterStats(URPGBattleCharacterStatsComponent* InCharacterStats)
{
	CharacterStats = InCharacterStats;
}

URPGBattleManagerComponent* ARPGBattleCharacter::GetBattleManager()
{
	return BattleManagerRef;
}

void ARPGBattleCharacter::SetBattleManager(URPGBattleManagerComponent* InBattleManagerRef)
{
	BattleManagerRef = InBattleManagerRef;
}

URPGTargetingManagerComponent* ARPGBattleCharacter::GetTargetingManager()
{
	return TargetingManagerRef;
}

void ARPGBattleCharacter::SetTargetingManager(URPGTargetingManagerComponent* InTargetingManagerRef)
{
	TargetingManagerRef = InTargetingManagerRef;
}

bool ARPGBattleCharacter::GetBIsControlledByAI()
{
	return bIsControlledByAI;
}

void ARPGBattleCharacter::SetBIsControlledByAI(bool InBIsControlledByAI)
{
	bIsControlledByAI = InBIsControlledByAI;
}

bool ARPGBattleCharacter::GetBIsDead()
{
	return bIsDead;
}

void ARPGBattleCharacter::SetBIsDead(bool InBIsDead)
{
	bIsDead = InBIsDead;
}

TArray<ARPGBattleCharacter*> ARPGBattleCharacter::GetTargetedCharacters()
{
	return TargetedCharacters;
}

void ARPGBattleCharacter::SetTargetedCharacters(TArray<ARPGBattleCharacter*> InTargetedCharacters)
{
	TargetedCharacters = InTargetedCharacters;
}

bool ARPGBattleCharacter::GetBIsEnemy()
{
	return bIsEnemy;
}

void ARPGBattleCharacter::SetBIsEnemy(bool InBIsEnemy)
{
	bIsEnemy = InBIsEnemy;
}

void ARPGBattleCharacter::OnDamageReceived_Implementation(float Damage, bool bIsCritical)
{
	ARPGDamagePopUp* DamagePopUp = Cast<ARPGDamagePopUp>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, ARPGDamagePopUp::StaticClass(), GetTransform()));

	if (DamagePopUp)
	{
		DamagePopUp->Value = Damage;
		DamagePopUp->bIsCritical = bIsCritical;

		DamagePopUp->Init();

		UGameplayStatics::FinishSpawningActor(DamagePopUp, GetTransform());
	}
}

void ARPGBattleCharacter::OnDeath_Implementation()
{
	
}

void ARPGBattleCharacter::OnHealed_Implementation(float HealAmmount, bool bIsMPRestored)
{
	ARPGDamagePopUp* DamagePopUp = Cast<ARPGDamagePopUp>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, ARPGDamagePopUp::StaticClass(), GetTransform()));

	if (DamagePopUp)
	{
		DamagePopUp->Value = HealAmmount;
		DamagePopUp->bIsHealing = bIsMPRestored;

		DamagePopUp->Init();

		UGameplayStatics::FinishSpawningActor(DamagePopUp, GetTransform());
	}
}

void ARPGBattleCharacter::OnInitiativeReduced_Implementation(float ReductionAmmount)
{
	ARPGDamagePopUp* DamagePopUp = Cast<ARPGDamagePopUp>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, ARPGDamagePopUp::StaticClass(), GetTransform()));

	if (DamagePopUp)
	{
		DamagePopUp->Value = ReductionAmmount;
		DamagePopUp->bIsReducingInitiative = true;

		DamagePopUp->Init();

		UGameplayStatics::FinishSpawningActor(DamagePopUp, GetTransform());
	}
}

void ARPGBattleCharacter::OnResurrected_Implementation(float HealAmmount)
{
	ARPGDamagePopUp* DamagePopUp = Cast<ARPGDamagePopUp>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, ARPGDamagePopUp::StaticClass(), GetTransform()));

	if (DamagePopUp)
	{
		DamagePopUp->Value = HealAmmount;
		DamagePopUp->bIsHealing = true;

		DamagePopUp->Init();

		UGameplayStatics::FinishSpawningActor(DamagePopUp, GetTransform());
	}
}

void ARPGBattleCharacter::ExecuteAction(ActionTypeEnum InActionType, FName InSecondaryActionName)
{
	switch (InActionType)
	{
	case ActionTypeEnum::EAttack:
		ExecuteAttackAction();
		break;
	case ActionTypeEnum::EDefend:
		ExecuteDefendAction();
		break;
	case ActionTypeEnum::EItems:
		ExecuteItemAction(InSecondaryActionName);
		break;
	case ActionTypeEnum::EMagic:
		ExecuteMagicAction(InSecondaryActionName);
		break;
	case ActionTypeEnum::EFlee:
		ExecuteFleeAction();
		break;
	default:
		break;
	}
}

void ARPGBattleCharacter::ExecuteAttackAction()
{

}

void ARPGBattleCharacter::ExecuteDefendAction()
{

}

void ARPGBattleCharacter::ExecuteItemAction(FName InItemName)
{

}

void ARPGBattleCharacter::ExecuteMagicAction(FName InMagicName)
{

}

void ARPGBattleCharacter::ExecuteFleeAction()
{

}

void ARPGBattleCharacter::TestFunc()
{
	UE_LOG(LogTemp, Warning, TEXT("AFTER"));
}