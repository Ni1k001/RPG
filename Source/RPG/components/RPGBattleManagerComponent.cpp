// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGBattleManagerComponent.h"

#include "RPG/RPGDataTables.h"
#include "RPG/RPGGameInstance.h"

#include "RPG/battle/RPGBattleCharacter.h"
#include "RPG/battle/RPGCharacterBattleSpot.h"
#include "RPG/battle/RPGEnemyBattleSpot.h"

#include "RPG/components/RPGTargetingManagerComponent.h"
#include "RPG/components/RPGBattleCharacterStatsComponent.h"

#include "RPG/widgets/battle/RPGBattleCharacterSlotWidget.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
URPGBattleManagerComponent::URPGBattleManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void URPGBattleManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void URPGBattleManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

/*				DEFAULT				*/
float URPGBattleManagerComponent::GetRequiredInitiative()
{
	return RequiredInitiative;
}

void URPGBattleManagerComponent::SetRequiredInitiative(float InRequiredInitiative)
{
	RequiredInitiative = InRequiredInitiative;
}

ARPGBattleCharacter* URPGBattleManagerComponent::GetCurrentCharacter()
{
	return CurrentCharacter;
}

void URPGBattleManagerComponent::SetCurrentCharacter(ARPGBattleCharacter* InCharacter)
{
	CurrentCharacter = InCharacter;
}

TArray<ARPGBattleCharacter*> URPGBattleManagerComponent::GetPlayerCharacters()
{
	return PlayerCharacters;
}

void URPGBattleManagerComponent::SetPlayerCharacters(TArray<ARPGBattleCharacter*> InPlayerCharacters)
{
	PlayerCharacters = InPlayerCharacters;
}

TArray<ARPGBattleCharacter*> URPGBattleManagerComponent::GetEnemyCharacters()
{
	return EnemyCharacters;
}

void URPGBattleManagerComponent::SetEnemyCharacters(TArray<ARPGBattleCharacter*> InEnemyCharacters)
{
	EnemyCharacters = InEnemyCharacters;
}

/*				PRE BATTLE				*/
void URPGBattleManagerComponent::EncounteredEnemies(FName InEncounterName, FName InBattleMapName)
{
	FSoftObjectPath DataTableLoader = TEXT("/Game/DataTables/EncountersDataTable.EncountersDataTable");
	UDataTable* DataTable = Cast<UDataTable>(DataTableLoader.TryLoad());
	FString ContextString;
	if (DataTable)
	{
		FEncountersTable* row = DataTable->FindRow<FEncountersTable>(InEncounterName, ContextString);

		OpenBattleMap(InBattleMapName, row->Enemies);
	}
}

void URPGBattleManagerComponent::OpenBattleMap(FName InBattleMapName, TMap<int32, FName> InEncounteredEnemies)
{
	URPGGameInstance* GI = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());
	GI->SetEncounteredEnemies(InEncounteredEnemies);
	GI->SetWorldTransformBeforeBattle(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorTransform());
	GI->SetCameraRotationBeforeBattle(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetControlRotation());
	GI->SetEnemiesTransformsBeforeBattle(GetWorldEnemiesTransforms());

	FLatentActionInfo LatentInfo;

	UGameplayStatics::GetStreamingLevel(GetWorld(), GI->GetWorldMapName())->SetShouldBeVisible(false);
	UGameplayStatics::LoadStreamLevel(GetWorld(), InBattleMapName, false, false, LatentInfo);
	UGameplayStatics::UnloadStreamLevel(GetWorld(), GI->GetWorldMapName(), LatentInfo, false);
	UGameplayStatics::GetStreamingLevel(GetWorld(), InBattleMapName)->SetShouldBeVisible(true);
}

TMap<FName, FTransform> URPGBattleManagerComponent::GetWorldEnemiesTransforms()
{
	TMap<FName, FTransform> EnemiesTransforms;

	for (TActorIterator<ARPGCharacter> It(GetWorld(), ARPGCharacter::StaticClass()); It; ++It)
	{
		ARPGCharacter* Actor = Cast<ARPGCharacter>(*It);
		if (Actor && !Actor->IsPendingKill())
		{
			EnemiesTransforms.FindOrAdd(Actor->GetFName(), Actor->GetActorTransform()); //Change ARPGCharacter to EnemyCharacter + get proper name
		}
	}
	return EnemiesTransforms;
}

/*				BATTLE INITIALIZATION				*/
void URPGBattleManagerComponent::SpawnPlayerTeam()
{
	URPGGameInstance* GI = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());
 
	//TODO
	for (int i = 0; i < GI->GetParty().Num(); i++)
	{
		FTransform SpawnTransform = GetBattleSpawnPointTransform(false, i);

		ARPGBattleCharacter* Character = Cast<ARPGBattleCharacter>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, ARPGBattleCharacter::StaticClass(), SpawnTransform));

		if (Character)
		{
			Character->SetBIsControlledByAI(false);
			Character->SetBattleManager(this);
			Character->SetBIsEnemy(false);
			Character->SetTargetingManager(Cast<URPGTargetingManagerComponent>(GetOwner()->GetComponentByClass(URPGTargetingManagerComponent::StaticClass())));

			UGameplayStatics::FinishSpawningActor(Character, SpawnTransform);

			FCharacterInfoStruct* CurrChar = GI->GetCharacters().Find(GI->GetParty()[i].Name);

			Character->GetCharacterStats()->SetCharacterData(CurrChar->DisplayName, CurrChar->Stats, CurrChar->DerivedStats, CurrChar->CurrentHP, CurrChar->CurrentMP);

			PlayerCharacters.Add(Character);

			Character->GetCharacterStats()->CreateCharacterBattleSlot();
			Character->GetCharacterStats()->SetBattleManagerRef(this);

			if (Character->GetCharacterStats()->GetCurrentHP() == 0)
			{
				PlayerCharacters.Remove(Character);
				DeadPlayerCharacters.Add(Character);

				Character->GetCharacterStats()->GetBattleCharacterSlotRef()->DarkenSlotOnDeath();
				Character->SetBIsDead(true);
			}
		}
	}
}

void URPGBattleManagerComponent::SpawnEnemyTeam()
{
	URPGGameInstance* GI = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());

	for (int i = 0; i < GI->GetEncounteredEnemies().Num(); i++)
	{
		//Datatable
//		GI->GetEncounteredEnemies().Find(i);

		FTransform SpawnTransform = GetBattleSpawnPointTransform(true, i);

		ARPGBattleCharacter* Character = Cast<ARPGBattleCharacter>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, ARPGBattleCharacter::StaticClass(), SpawnTransform));

		if (Character)
		{
			Character->SetBIsControlledByAI(true);
			Character->SetBattleManager(this);
			Character->SetBIsEnemy(true);
			Character->SetTargetingManager(Cast<URPGTargetingManagerComponent>(GetOwner()->GetComponentByClass(URPGTargetingManagerComponent::StaticClass())));

			UGameplayStatics::FinishSpawningActor(Character, SpawnTransform);

			Character->GetCharacterStats()->SetBattleManagerRef(this);
//			Character->GetCharacterStats()->SetCharacterData();

			EnemyCharacters.Add(Character);
		}
	}
}

FTransform URPGBattleManagerComponent::GetBattleSpawnPointTransform(bool bEnemySpot, int32 SpotIndex)
{
	if (bEnemySpot)
	{
		for (TActorIterator<ARPGEnemyBattleSpot> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			if (ActorItr->GetSlotIndex() == SpotIndex)
			{
				ActorItr->GetActorLocation();
				ActorItr->GetArrowComponent()->GetComponentRotation();
				ActorItr->GetArrowComponent()->GetComponentScale();

				return FTransform(ActorItr->GetArrowComponent()->GetComponentRotation(), ActorItr->GetActorLocation(), ActorItr->GetArrowComponent()->GetComponentScale());
			}
		}

		return FTransform(ENoInit::NoInit);
	}
	
	for (TActorIterator<ARPGCharacterBattleSpot> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->GetSlotIndex() == SpotIndex)
		{
			ActorItr->GetActorLocation();
			ActorItr->GetArrowComponent()->GetComponentRotation();
			ActorItr->GetArrowComponent()->GetComponentScale();

			return FTransform(ActorItr->GetArrowComponent()->GetComponentRotation(), ActorItr->GetActorLocation(), ActorItr->GetArrowComponent()->GetComponentScale());
		}
	}
	
	return FTransform(ENoInit::NoInit);
}

/*				BATTLE IN PROGRESS				*/
void URPGBattleManagerComponent::GetCharacterWithMaxInitiative(bool& Success, ARPGBattleCharacter*& Character)
{
	//TODO
	Character = GetCurrentCharacter();

	/*for each (ACharacter* PlayerCharacter in PlayerCharacters)
	{

	}

	for each (ACharacter* EnemyCharacter in EnemyCharacters)
	{

	}*/

	if (Character)
		Success = true;
	else
		Success = false;
}

void URPGBattleManagerComponent::StartCharacterTurn(ARPGBattleCharacter* InCharacter)
{

}

void URPGBattleManagerComponent::SelectAction(ActionTypeEnum InActionType)
{

}

void URPGBattleManagerComponent::RequestActionExecution(TArray<ARPGBattleCharacter*> InTargetedCharacters)
{

}

void URPGBattleManagerComponent::SelectSecondaryAction(FName InSelectedSecondaryAction)
{

}

void URPGBattleManagerComponent::DisableTargetingAndInput(ARPGBattleCharacter* InEnemy)
{

}

void URPGBattleManagerComponent::OnEnemyKilled(ARPGBattleCharacter* InEnemy)
{

}

void URPGBattleManagerComponent::OnPlayerCharacterKilled(ARPGBattleCharacter* InPlayerCharacter)
{

}

void URPGBattleManagerComponent::OnPlayerCharacterResurrected(ARPGBattleCharacter* InPlayerCharacter)
{

}

TArray<FItemDataStruct> URPGBattleManagerComponent::GetAllItemsUsableInBattle(TArray<FItemDataStruct> InInventory)
{
	return InInventory;
}

void URPGBattleManagerComponent::EndCharacterTurn(float InUsedInitiative)
{

}

void URPGBattleManagerComponent::ShowActionWidget()
{

}

void URPGBattleManagerComponent::HideActionWidget()
{

}

void URPGBattleManagerComponent::ShowBattleTooltip(FText InTooltipText)
{

}

//		 GetProperSecondaryActionSlotWidget(int32 InSlotIndex);

/*				BATTLE END				*/
void URPGBattleManagerComponent::ReturnToWorldMap()
{
	URPGGameInstance* GI = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());
	FName BattleMapName;
	FLatentActionInfo LatentInfo;
	auto strlvl = GetWorld()->GetStreamingLevels();

	for (auto& lvl : strlvl)
	{
		if (lvl->IsLevelLoaded() && lvl->IsLevelVisible())
		{
			BattleMapName = lvl->GetWorldAssetPackageFName();
		}
	}

	UGameplayStatics::GetStreamingLevel(GetWorld(), BattleMapName)->SetShouldBeVisible(false);
	UGameplayStatics::LoadStreamLevel(GetWorld(), GI->GetWorldMapName(), false, false, LatentInfo);
	UGameplayStatics::UnloadStreamLevel(GetWorld(), BattleMapName, LatentInfo, false);
	UGameplayStatics::GetStreamingLevel(GetWorld(), GI->GetWorldMapName())->SetShouldBeVisible(true);

	ARPGCharacter* Player = Cast<ARPGCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());

	if (Player)
	{

		Player->GetMovementComponent()->StopMovementImmediately();
		Player->SetActorTransform(GI->GetWorldTransformBeforeBattle());
	}
}

void URPGBattleManagerComponent::RollBattleRewards()
{

}

void URPGBattleManagerComponent::CheckIfAlreadyLootedItem()
{

}

void URPGBattleManagerComponent::ReceiveBattleRewards()
{

}

void URPGBattleManagerComponent::ShowBattleEndScreen()
{

}

void URPGBattleManagerComponent::CreateBattleInterface()
{

}

void URPGBattleManagerComponent::UpdateBattleEndScreenOnClick()
{

}