// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGBattleManagerComponent.h"
#include "Kismet/GameplayStatics.h"

#include "RPG/RPGCharacter.h"
#include "RPG/RPGDataTables.h"
#include "RPG/RPGGameInstance.h"

#include "RPG/battle/RPGBattleCharacter.h"
#include "RPG/battle/RPGCharacterBattleSpot.h"
#include "RPG/battle/RPGEnemyBattleSpot.h"

#include "RPG/components/RPGBattleCharacterStatsComponent.h"
#include "RPG/components/RPGCharactersManagerComponent.h"
#include "RPG/components/RPGDynamicCameraManagerComponent.h"
#include "RPG/components/RPGTargetingManagerComponent.h"

#include "RPG/widgets/battle/RPGBattleCharacterSlotWidget.h"

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

//

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

TArray<ARPGBattleCharacter*> URPGBattleManagerComponent::GetDeadPlayerCharacters()
{
	return DeadPlayerCharacters;
}

void URPGBattleManagerComponent::SetDeadPlayerCharacters(TArray<ARPGBattleCharacter*> InDeadPlayerCharacters)
{
	DeadPlayerCharacters = InDeadPlayerCharacters;
}

TArray<ARPGBattleCharacter*> URPGBattleManagerComponent::GetDeadEnemyCharacters()
{
	return DeadEnemyCharacters;
}

void URPGBattleManagerComponent::SetDeadEnemyCharacters(TArray<ARPGBattleCharacter*> InDeadEnemyCharacters)
{
	DeadEnemyCharacters = InDeadEnemyCharacters;
}

ActionTypeEnum URPGBattleManagerComponent::GetSelectedAction()
{
	return SelectedAction;
}

void URPGBattleManagerComponent::SetSelectedAction(ActionTypeEnum InSelectedAction)
{
	SelectedAction = InSelectedAction;
}

FName URPGBattleManagerComponent::GetSelectedSecondaryAction()
{
	return SelectedSecondaryAction;
}

void URPGBattleManagerComponent::SetSelectedSecondaryAction(FName InSelectedSecondaryAction)
{
	SelectedSecondaryAction = InSelectedSecondaryAction;
}

/*				PRE BATTLE				*/
void URPGBattleManagerComponent::EncounteredEnemies(FName InEncounterName, FName InBattleMapName) //DONE
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

void URPGBattleManagerComponent::OpenBattleMap(FName InBattleMapName, TMap<int32, FName> InEncounteredEnemies) //?
{
	URPGGameInstance* GI = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());
	GI->SetEncounteredEnemies(InEncounteredEnemies);
	GI->SetWorldTransformBeforeBattle(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorTransform());
	GI->SetCameraRotationBeforeBattle(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetControlRotation());
	GI->SetEnemiesTransformsBeforeBattle(GetWorldEnemiesTransforms());
	GI->SetBattleArenaName(InBattleMapName);

	FLatentActionInfo LatentInfo;

	UGameplayStatics::GetStreamingLevel(GetWorld(), GI->GetWorldMapName())->SetShouldBeVisible(false);
	UGameplayStatics::LoadStreamLevel(GetWorld(), InBattleMapName, false, false, LatentInfo);
	UGameplayStatics::UnloadStreamLevel(GetWorld(), GI->GetWorldMapName(), LatentInfo, true);
	UGameplayStatics::GetStreamingLevel(GetWorld(), InBattleMapName)->SetShouldBeVisible(true);
}

TMap<FName, FTransform> URPGBattleManagerComponent::GetWorldEnemiesTransforms() //TODO
{
	TMap<FName, FTransform> EnemiesTransforms;

	for (TActorIterator<ARPGCharacter> It(GetWorld(), ARPGCharacter::StaticClass()); It; ++It)
	{
		ARPGCharacter* Actor = Cast<ARPGCharacter>(*It);
		//if (Actor && !Actor->IsPendingKill())
		if (Actor)
		{
			EnemiesTransforms.Add(Actor->GetFName(), Actor->GetActorTransform()); //Change ARPGCharacter to EnemyCharacter + get proper name
		}
	}
	return EnemiesTransforms;
}

/*				BATTLE INITIALIZATION				*/
void URPGBattleManagerComponent::SpawnPlayerTeam() //DONE
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

void URPGBattleManagerComponent::SpawnEnemyTeam() //DONE
{
	URPGGameInstance* GI = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());

	for (int i = 0; i < GI->GetEncounteredEnemies().Num(); i++)
	{
		FSoftObjectPath DataTableLoader = TEXT("/Game/DataTables/EnemiesDataTable.EnemiesDataTable");
		UDataTable* DataTable = Cast<UDataTable>(DataTableLoader.TryLoad());
		FString ContextString;
		if (DataTable)
		{
			FEnemiesTable* row = DataTable->FindRow<FEnemiesTable>(GI->GetEncounteredEnemies().FindRef(i), ContextString);
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
				Character->GetCharacterStats()->SetCharacterData(row->DisplayName, row->Stats, row->DerivedStats, *row->Stats.Find(StatsEnum::EHP), *row->Stats.Find(StatsEnum::EMP));

				EnemyCharacters.Add(Character);
			}
		}
	}
}

FTransform URPGBattleManagerComponent::GetBattleSpawnPointTransform(bool bEnemySpot, int32 SpotIndex) //DONE
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
void URPGBattleManagerComponent::GetCharacterWithMaxInitiative(bool& bOutSuccess, ARPGBattleCharacter*& OutCharacter) //DONE
{
	OutCharacter = GetCurrentCharacter();

	for (int i = 0; i < PlayerCharacters.Num(); i++)
	{
		if (PlayerCharacters[i]->GetCharacterStats()->GetCurrentInitiative() >= RequiredInitiative)
		{
			bOutSuccess = true;
			OutCharacter = PlayerCharacters[i];
			return;
		}
	}
	
	for (int i = 0; i < EnemyCharacters.Num(); i++)
	{
		if (EnemyCharacters[i]->GetCharacterStats()->GetCurrentInitiative() >= RequiredInitiative)
		{
			bOutSuccess = true;
			OutCharacter = EnemyCharacters[i];
			return;
		}
	}
}

void URPGBattleManagerComponent::StartCharacterTurn(ARPGBattleCharacter* InCharacter) //TODO
{
	CurrentCharacter = InCharacter;

	if (!CurrentCharacter->GetBIsControlledByAI())
	{
		CurrentCharacter->GetCharacterStats()->SetBIsDefending(false);
		
		Cast<URPGDynamicCameraManagerComponent>(GetOwner()->GetComponentByClass(URPGDynamicCameraManagerComponent::StaticClass()))->SetNewDynamicPath("Ally_General", true, true, true, CurrentCharacter->GetActorLocation());
	
		if (CurrentCharacter->GetCharacterStats()->GetBattleCharacterSlotRef()->IsValidLowLevel())
		{
			CurrentCharacter->GetCharacterStats()->GetBattleCharacterSlotRef()->HighlightSlot();
			//CurrentCharacter->GetCharacterStats()->GetBattleCharacterSlotRef()->
			
			//Gamepad
		}
	}
	else
	{
		//CurrentCharacter->PerformActionByAI();
	}
}

void URPGBattleManagerComponent::SelectAction(ActionTypeEnum InActionType) //TODO
{
	SelectedAction = InActionType;

	switch (InActionType)
	{
	case ActionTypeEnum::EAttack:
	case ActionTypeEnum::EDefend:
	case ActionTypeEnum::EFlee:
//		IsValid(GetOwner()->GetComponentByClass())
		break;
	case ActionTypeEnum::EItems:
		CurrentCharacter->GetCharacterStats()->SetSelectedActonType(InActionType);
		//
		break;
	case ActionTypeEnum::EMagic:
		CurrentCharacter->GetCharacterStats()->SetSelectedActonType(InActionType);
		//
		break;
	default:
		break;
	}
}

void URPGBattleManagerComponent::RequestActionExecution(TArray<ARPGBattleCharacter*> InTargetedCharacters) //DONE
{
	CurrentCharacter->GetCharacterStats()->SetTargetedCharacters(InTargetedCharacters);

	CurrentCharacter->ExecuteAction(SelectedAction, SelectedSecondaryAction);

	DisableTargetingAndInput();
}

void URPGBattleManagerComponent::SelectSecondaryAction(FName InSelectedSecondaryAction) //TODO
{
	SelectedSecondaryAction = InSelectedSecondaryAction;

	//if (IsValid(GetOwner()->))
}

void URPGBattleManagerComponent::DisableTargetingAndInput() //DONE
{
	if (IsValid(GetOwner()->GetComponentByClass(URPGTargetingManagerComponent::StaticClass())))
	{
		URPGTargetingManagerComponent* TMC = Cast<URPGTargetingManagerComponent>(GetOwner()->GetComponentByClass(URPGTargetingManagerComponent::StaticClass()));
		
		TMC->DisableTargeting();
		TMC->HideTargets();
	}
}

void URPGBattleManagerComponent::OnEnemyKilled(ARPGBattleCharacter* InEnemy) //DONE
{
	InEnemy->GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);

	EnemyCharacters.Remove(InEnemy);
	DeadEnemyCharacters.Add(InEnemy);

	if (EnemyCharacters.Num() == 0)
		EndBattle();
}

void URPGBattleManagerComponent::OnPlayerCharacterKilled(ARPGBattleCharacter* InPlayerCharacter) //DONE
{
	PlayerCharacters.Remove(InPlayerCharacter);
	DeadPlayerCharacters.Add(InPlayerCharacter);

	InPlayerCharacter->GetCharacterStats()->GetBattleCharacterSlotRef()->DarkenSlotOnDeath();

	if (PlayerCharacters.Num() == 0)
		GameOver();
}

void URPGBattleManagerComponent::OnPlayerCharacterResurrected(ARPGBattleCharacter* InPlayerCharacter) //TODO
{
	DeadPlayerCharacters.Remove(InPlayerCharacter);
	PlayerCharacters.Add(InPlayerCharacter);

	InPlayerCharacter->GetCharacterStats()->GetBattleCharacterSlotRef()->RestoreSlotOnResurrection();
}

TArray<FItemDataStruct> URPGBattleManagerComponent::GetAllItemsUsableInBattle(TArray<FItemDataStruct> InInventory) //TODO
{
	return InInventory;

	TArray<FName> AddedItems;
	for (int i = 0; i < InInventory.Num(); i++)
	{
		if (InInventory[i].BaseItemData.bCanBeUsedInBattle)
		{
			if (!AddedItems.Contains(InInventory[i].BaseItemData.ItemName))
			{
				AddedItems.Add(InInventory[i].BaseItemData.ItemName);

				//GetOwner()->GetComponentByClass();
			}
		}
	}
}

void URPGBattleManagerComponent::EndCharacterTurn(float InUsedInitiative) //TODO
{
	CurrentCharacter->GetCharacterStats()->RemoveInitiative(InUsedInitiative);
	
	HideActionWidget();

	if (CurrentCharacter->GetCharacterStats()->GetBattleCharacterSlotRef()->IsValidLowLevel())
	{
		CurrentCharacter->GetCharacterStats()->GetBattleCharacterSlotRef()->UnhighlightSlot();

		//

		Cast<URPGDynamicCameraManagerComponent>(GetOwner()->GetComponentByClass(URPGDynamicCameraManagerComponent::StaticClass()))->SetNewDynamicPath("Overview", true, true, false, FVector(0.f, 0.f, 0.f));
	}
}

void URPGBattleManagerComponent::ShowActionWidget() //TODO
{

}

void URPGBattleManagerComponent::HideActionWidget() //TODO
{

}

void URPGBattleManagerComponent::ShowBattleTooltip(FText InTooltipText) //TODO
{

}

//		 GetProperSecondaryActionSlotWidget(int32 InSlotIndex);

/*				BATTLE END				*/
void URPGBattleManagerComponent::ReturnToWorldMap() //DONE
{
	URPGGameInstance* GI = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());
	
	TMap<FName, FCharacterInfoStruct> Characters = GI->GetCharacters();


	for (int i = 0; i < PlayerCharacters.Num(); i++)
	{
		FCharacterInfoStruct* CIS = Characters.Find(PlayerCharacters[i]->GetCharacterStats()->GetHardcodedName());

		CIS->CurrentHP = PlayerCharacters[i]->GetCharacterStats()->GetCurrentHP();
		CIS->CurrentMP = PlayerCharacters[i]->GetCharacterStats()->GetCurrentMP();

		Characters.Add(CIS->Name, *CIS);

		GI->SetCharacters(Characters);
	}

	for (int i = 0; i < DeadPlayerCharacters.Num(); i++)
	{
		FCharacterInfoStruct* CIS = Characters.Find(DeadPlayerCharacters[i]->GetCharacterStats()->GetHardcodedName());

		CIS->CurrentHP = DeadPlayerCharacters[i]->GetCharacterStats()->GetCurrentHP();
		CIS->CurrentMP = DeadPlayerCharacters[i]->GetCharacterStats()->GetCurrentMP();

		Characters.Add(CIS->Name, *CIS);

		GI->SetCharacters(Characters);
	}

	GI->SetBSpawningAfterBattle(true);

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
	UGameplayStatics::UnloadStreamLevel(GetWorld(), BattleMapName, LatentInfo, false);
	UGameplayStatics::LoadStreamLevel(GetWorld(), GI->GetWorldMapName(), false, false, LatentInfo);
	UGameplayStatics::GetStreamingLevel(GetWorld(), GI->GetWorldMapName())->SetShouldBeVisible(true);

	ARPGCharacter* Player = Cast<ARPGCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());

	if (Player)
	{
		Player->GetMovementComponent()->StopMovementImmediately();
		Player->SetActorTransform(GI->GetWorldTransformBeforeBattle());
	}

	GI->SetBattleArenaName("None");
}

void URPGBattleManagerComponent::RollBattleRewards(int32& OutExperience, int32& OutGold, TArray<FItemDataStruct>& OutItemsLooted) //TODO
{
	URPGGameInstance* GI = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());

	int32 Exp = 0;
	int32 Gold = 0;
	TArray<FItemDataStruct> Items;

	FSoftObjectPath DataTableLoader = TEXT("/Game/DataTables/EnemiesDataTable.EnemiesDataTable");
	UDataTable* DataTable = Cast<UDataTable>(DataTableLoader.TryLoad());
	FString ContextString;
	if (DataTable)
	{
		for (int i = 0; i < DeadEnemyCharacters.Num(); i++)
		{
			FEnemiesTable* row = DataTable->FindRow<FEnemiesTable>(DeadEnemyCharacters[i]->GetCharacterStats()->GetHardcodedName(), ContextString);

			Exp += row->ExperienceReward;
			Gold += row->GoldReward;

			//Loot
		}

		OutExperience = Exp;
		OutGold = Gold;
		OutItemsLooted = Items;
	}
}

void URPGBattleManagerComponent::CheckIfAlreadyLootedItem(FName InItemName, TArray<FItemDataStruct> InLootedItems, bool& OutBIsAlreadyLooted, int32& OutSlotIndex) //DONE
{
	for (int i = 0; i < InLootedItems.Num(); i++)
	{
		if (InItemName == InLootedItems[i].BaseItemData.ItemName)
		{
			OutBIsAlreadyLooted = true;
			OutSlotIndex = i;
			break;
		}
	}
}

void URPGBattleManagerComponent::ReceiveBattleRewards(int32 InExperience, int32 InGold, TArray<FItemDataStruct> InItemsLooted)// TODO
{
	for (int i = 0; PlayerCharacters.Num(); i++)
	{
		//Cast<URPGCharactersManagerComponent>(GetOwner()->GetComponentByClass(URPGCharactersManagerComponent::StaticClass()))
		PlayerCharacters[i]->GetCharacterStats()->GetHardcodedName();
	}

	//InventoryManager AddGold AddItems
}

void URPGBattleManagerComponent::ShowBattleEndScreen() //TODO
{

}

void URPGBattleManagerComponent::CreateBattleInterface() //TODO
{

}

void URPGBattleManagerComponent::UpdateBattleEndScreenOnClick() //TODO
{

}

/*				BATTLE					*/
void URPGBattleManagerComponent::ResumeBattle() //DONE
{
	AddInitiativeToAllCharacters();
}

void URPGBattleManagerComponent::AddInitiativeToAllCharacters() //DONE?
{
	if (PlayerCharacters.Num() > 0 && EnemyCharacters.Num() > 0)
	{
		bool bIsSuccess;
		ARPGBattleCharacter* Character;

		GetCharacterWithMaxInitiative(bIsSuccess, Character);

		if (bIsSuccess)
		{
			StartCharacterTurn(Character);
		}
		else
		{
			for (int i = 0; i < PlayerCharacters.Num(); i++)
				PlayerCharacters[i]->GetCharacterStats()->AddInitiative(0.f);

			for (int i = 0; i < EnemyCharacters.Num(); i++)
				EnemyCharacters[i]->GetCharacterStats()->AddInitiative(0.f);

			AddInitiativeToAllCharacters();
		}
	}
}

void URPGBattleManagerComponent::EndBattle() //TODO?
{
	ShowBattleEndScreen();

	//Gamepad
}

void URPGBattleManagerComponent::GameOver() //TODO
{

}