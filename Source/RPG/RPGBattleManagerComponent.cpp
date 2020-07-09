// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGBattleManagerComponent.h"
#include "RPGDataTables.h"
#include "RPGGameInstance.h"
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

ACharacter* URPGBattleManagerComponent::GetCurrentCharacter() //Change to BattleCharacterBase
{
	return CurrentCharacter;
}

void URPGBattleManagerComponent::SetCurrentCharacter(ACharacter* InCharacter) //Change to BattleCharacterBase
{
	CurrentCharacter = InCharacter;
}

TArray<ARPGCharacter*> URPGBattleManagerComponent::GetPlayerCharacters() //Change to BattleCharacterBase
{
	return PlayerCharacters;
}

void URPGBattleManagerComponent::SetPlayerCharacters(TArray<ARPGCharacter*> InPlayerCharacters) //Change to BattleCharacterBase
{
	PlayerCharacters = InPlayerCharacters;
}

TArray<ACharacter*> URPGBattleManagerComponent::GetEnemyCharacters() //Change to BattleCharacter
{
	return EnemyCharacters;
}

void URPGBattleManagerComponent::SetEnemyCharacters(TArray<ACharacter*> InEnemyCharacters) //Change to BattleCharacterBase
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
		
	}
}

void URPGBattleManagerComponent::SpawnEnemyTeam()
{
	
}

FTransform URPGBattleManagerComponent::GetBattleSpawnPointTransform(bool bEnemySpot, int32 SpotIndex)
{
	//TODO

	if (bEnemySpot)
	{
		return FTransform(ENoInit::NoInit);
	}

	return FTransform(ENoInit::NoInit);
}

/*				BATTLE IN PROGRESS				*/
void URPGBattleManagerComponent::GetCharacterWithMaxInitiative(bool& Success, ACharacter*& Character) //Change to BattleCharacterBase
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

void URPGBattleManagerComponent::StartCharacterTurn(ACharacter* Character) //Change to BattleCharacterBase
{

}

void URPGBattleManagerComponent::EndCharacterTurn()
{

}

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