// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGTargetingManagerComponent.h"
#include "Components/BillboardComponent.h"

#include "RPG/RPGGameInstance.h"

#include "RPG/battle/RPGBattleCharacter.h"

#include "RPG/components/RPGBattleManagerComponent.h"
#include "RPG/components/RPGDynamicCameraManagerComponent.h"

// Sets default values for this component's properties
URPGTargetingManagerComponent::URPGTargetingManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URPGTargetingManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	while (!GameInstance)
	{
		GameInstance = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());
	}
}


// Called every frame
void URPGTargetingManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool URPGTargetingManagerComponent::GetBIsTargetingEnabled()
{
	return bIsTargetingEnabled;
}

bool URPGTargetingManagerComponent::GetBCanTargetSelf()
{
	return bCanTargetSelf;
}

TargetingTypeEnum URPGTargetingManagerComponent::GetSelectedTargetingType()
{
	return SelectedTargetingType;
}

TArray<ARPGBattleCharacter*> URPGTargetingManagerComponent::GetTargetedCharacters()
{
	return TargetedCharacters;
}

void URPGTargetingManagerComponent::EnableTargeting(bool InBCanTargetSelf, TargetingTypeEnum InTargetingType)
{
	bCanTargetSelf = InBCanTargetSelf;
	SelectedTargetingType = InTargetingType;
	bIsTargetingEnabled = true;

	/*if ()
	{
		
	}*/

	switch (SelectedTargetingType)
	{
	case TargetingTypeEnum::EOOnlySelf:
	case TargetingTypeEnum::ESingleAlly:
	case TargetingTypeEnum::EAllAllies:
		if (GetOwner()->GetComponentByClass(URPGDynamicCameraManagerComponent::StaticClass()))
		{
			URPGDynamicCameraManagerComponent* DCM = Cast<URPGDynamicCameraManagerComponent>(GetOwner()->GetComponentByClass(URPGDynamicCameraManagerComponent::StaticClass()));
			DCM->SetNewDynamicPath(TEXT("Targeting_Ally"), true, true, false, FVector(0.f, 0.f, 0.f));
		}
		break;
	case TargetingTypeEnum::ESingleEnemy:
	case TargetingTypeEnum::EAllEnemies:
		if (GetOwner()->GetComponentByClass(URPGDynamicCameraManagerComponent::StaticClass()))
		{
			URPGDynamicCameraManagerComponent* DCM = Cast<URPGDynamicCameraManagerComponent>(GetOwner()->GetComponentByClass(URPGDynamicCameraManagerComponent::StaticClass()));
			DCM->SetNewDynamicPath(TEXT("Targeting_Enemy"), true, true, false, FVector(0.f, 0.f, 0.f));
		}
		break;
	default:
		break;
	}
}

void URPGTargetingManagerComponent::DisableTargeting()
{
	bIsTargetingEnabled = false;
}

void URPGTargetingManagerComponent::ShowTargets(ARPGBattleCharacter* InIndicatedCharacter)
{
	switch (SelectedTargetingType)
	{
	case TargetingTypeEnum::EOOnlySelf:
		if (InIndicatedCharacter->GetBattleManager()->GetCurrentCharacter() == InIndicatedCharacter)
		{
			InIndicatedCharacter->GetTarget()->SetHiddenInGame(false);
			TargetedCharacters.Add(InIndicatedCharacter);
		}
		break;
	case TargetingTypeEnum::ESingleAlly:
		if (!InIndicatedCharacter->GetBIsEnemy())
		{
			if (bCanTargetSelf || (!bCanTargetSelf && InIndicatedCharacter->GetBattleManager()->GetCurrentCharacter() != InIndicatedCharacter))
			{
				InIndicatedCharacter->GetTarget()->SetHiddenInGame(false);
				TargetedCharacters.Add(InIndicatedCharacter);
			}
		}
		break;
	case TargetingTypeEnum::ESingleEnemy:
		if (InIndicatedCharacter->GetBIsEnemy())
		{
			InIndicatedCharacter->GetTarget()->SetHiddenInGame(false);
			TargetedCharacters.Add(InIndicatedCharacter);
		}
		break;
	case TargetingTypeEnum::EAllAllies:
		if (!InIndicatedCharacter->GetBIsEnemy())
		{
			for (int i = 0; i < InIndicatedCharacter->GetBattleManager()->GetPlayerCharacters().Num(); i++)
			{
				if (bCanTargetSelf || (!bCanTargetSelf && InIndicatedCharacter->GetBattleManager()->GetCurrentCharacter() != InIndicatedCharacter->GetBattleManager()->GetPlayerCharacters()[i]))
				{
					InIndicatedCharacter->GetBattleManager()->GetPlayerCharacters()[i]->GetTarget()->SetHiddenInGame(false);
					TargetedCharacters.Add(InIndicatedCharacter->GetBattleManager()->GetPlayerCharacters()[i]);
				}
			}
		}
		break;
	case TargetingTypeEnum::EAllEnemies:
		if (InIndicatedCharacter->GetBIsEnemy())
		{
			for (int i = 0; i < InIndicatedCharacter->GetBattleManager()->GetEnemyCharacters().Num(); i++)
			{
				InIndicatedCharacter->GetBattleManager()->GetEnemyCharacters()[i]->GetTarget()->SetHiddenInGame(false);
				TargetedCharacters.Add(InIndicatedCharacter->GetBattleManager()->GetEnemyCharacters()[i]);
			}
		}
		break;
	default:
		break;
	}
}

void URPGTargetingManagerComponent::HideTargets()
{
	for (int i = 0; i < TargetedCharacters.Num(); i++)
	{
		TargetedCharacters[i]->GetTarget()->SetHiddenInGame(true);
	}

	TargetedCharacters.Empty();
}

void URPGTargetingManagerComponent::CancelTargeting()
{
	if (bIsTargetingEnabled)
	{
		bIsTargetingEnabled = false;

		if (GetOwner()->GetComponentByClass(URPGDynamicCameraManagerComponent::StaticClass()))
		{
			URPGDynamicCameraManagerComponent* DCM = Cast<URPGDynamicCameraManagerComponent>(GetOwner()->GetComponentByClass(URPGDynamicCameraManagerComponent::StaticClass()));
			DCM->SetNewDynamicPath(TEXT("Ally_General"), true, true, false, FVector(0.f, 0.f, 0.f));
		}
	}
}