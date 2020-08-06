// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine.h"

#include "RPG/RPGCharacter.h"
#include "RPG/RPGDataTables.h"
#include "RPG/RPGSaveGame.h"

#include "RPG/world/RPGSavePoint.h"

/*				DEFAULT				*/
void URPGGameInstance::Init()
{
	UGameInstance::Init();
	TimePlayed = new FTimespan(0,0,0,0,0);
	bCanSaveGame = false;
	BattleArenaName = "None";
}

void URPGGameInstance::OnStart()
{
	StartTime = new FTimespan(FDateTime::Now().GetTicks());
}

void URPGGameInstance::Shutdown()
{
	UpdateTimePlayed();
	UE_LOG(LogTemp, Warning, TEXT("%d:%d:%d"), FMath::FloorToInt(GetTimePlayed()->GetTotalHours()), GetTimePlayed()->GetMinutes(), GetTimePlayed()->GetSeconds());
}

FString URPGGameInstance::GetAppVersion()
{
	FString AppVersion;

	GConfig->GetString(TEXT("/Script/EngineSettings.GeneralProjectSettings"), TEXT("ProjectVersion"), AppVersion, GGameIni);

	return AppVersion;
}

bool URPGGameInstance::GetCanSaveGame()
{
	return bCanSaveGame;
}

void URPGGameInstance::SetCanSaveGame(bool InBCanSaveGame)
{
	bCanSaveGame = InBCanSaveGame;
}

FName URPGGameInstance::GetSavePointName()
{
	return SavePointName;
}

	/*				SAVED DATA				*/
void URPGGameInstance::SaveData(FString SaveSlotName, int32 UserIndex)
{
	if (bCanSaveGame)
	{
		UpdateTimePlayed();

		URPGSaveGame* SaveGameInstance = Cast<URPGSaveGame>(UGameplayStatics::CreateSaveGameObject(URPGSaveGame::StaticClass()));

		SaveGameInstance->Gold = GetGold();
		SaveGameInstance->Party = GetParty();
		SaveGameInstance->Characters = GetCharacters();
		SaveGameInstance->TimePlayed = *GetTimePlayed();
		SaveGameInstance->WorldMapName = GetWorldMapName();
		SaveGameInstance->SavePoint = GetSavePointName();
		SaveGameInstance->bRandomEncounter = GetRandomEncounter();
		SaveGameInstance->InteractedObjects = GetInteractedObjects();
		SaveGameInstance->BattledEnemies = GetBattledEnemies();

		UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveSlotName, (uint32)UserIndex);

		UE_LOG(LogTemp, Warning, TEXT("SAVED GOLD: %d"), GetGold());
		UE_LOG(LogTemp, Warning, TEXT("SAVED TIME: %d:%d:%d"), FMath::FloorToInt(GetTimePlayed()->GetTotalHours()), GetTimePlayed()->GetMinutes(), GetTimePlayed()->GetSeconds());
		UE_LOG(LogTemp, Warning, TEXT("CURRENT TIME: %d:%d:%d"), FMath::FloorToInt(SaveGameInstance->TimePlayed.GetTotalHours()), SaveGameInstance->TimePlayed.GetMinutes(), SaveGameInstance->TimePlayed.GetSeconds());
		UE_LOG(LogTemp, Warning, TEXT("SAVED SAVEPOINTNAME: %s"), *GetSavePointName().ToString());
	}
}

void URPGGameInstance::LoadData(FString SaveSlotName, int32 UserIndex)
{
	URPGSaveGame* LoadGameInstance = Cast<URPGSaveGame>(UGameplayStatics::CreateSaveGameObject(URPGSaveGame::StaticClass()));

	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, (uint32)UserIndex))
	{
		LoadGameInstance = Cast<URPGSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, (uint32)UserIndex));
		SetGold(LoadGameInstance->Gold);
		SetParty(LoadGameInstance->Party);
		SetCharacters(LoadGameInstance->Characters);
		SetTimePlayed(&LoadGameInstance->TimePlayed);
		SetWorldMapName(LoadGameInstance->WorldMapName);
		SetRandomEncounter(LoadGameInstance->bRandomEncounter);
		SetInteractedObjects(LoadGameInstance->InteractedObjects);
		SetBattledEnemies(LoadGameInstance->BattledEnemies);
		SetSavePointName(LoadGameInstance->SavePoint);

		StartTime = new FTimespan(FDateTime::Now().GetTicks());

		UE_LOG(LogTemp, Warning, TEXT("LOADED GOLD: %d"), GetGold());
		UE_LOG(LogTemp, Warning, TEXT("LOADED TIME: %d:%d:%d"), FMath::FloorToInt(LoadGameInstance->TimePlayed.GetTotalHours()), LoadGameInstance->TimePlayed.GetMinutes(), LoadGameInstance->TimePlayed.GetSeconds());
		UE_LOG(LogTemp, Warning, TEXT("CURRENT TIME: %d:%d:%d"), FMath::FloorToInt(GetTimePlayed()->GetTotalHours()), GetTimePlayed()->GetMinutes(), GetTimePlayed()->GetSeconds());
		UE_LOG(LogTemp, Warning, TEXT("LOADED SAVEPOINTNAME: %s"), *LoadGameInstance->SavePoint.ToString());

		ARPGCharacter* Player = Cast<ARPGCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());

		if (Player)
		{
			if (GetSavePointName().IsNone())
			{
				Player->GetMovementComponent()->StopMovementImmediately();
				Player->SetActorTransform(FTransform(FRotator(0.f, 0.f, 0.f), FVector(-770.f, 330.f, 260.f), FVector(1.f)));
			}
			else
			{
				for (FActorIterator It(GetWorld(), ARPGSavePoint::StaticClass()); It; ++It)
				{
					ARPGSavePoint* SavePoint = Cast<ARPGSavePoint>(*It);
					if (SavePoint)
					{
						if (SavePoint->GetSavePointName() == GetSavePointName())
						{
							//Player->SetActorLocation(SavePoint->SpawnPointCapsule->GetComponentLocation());
							Player->GetMovementComponent()->StopMovementImmediately();
							Player->SetActorTransform(FTransform(SavePoint->ArrowComponent->GetRelativeRotation(), SavePoint->SpawnPointCapsule->GetComponentLocation(), FVector(1.f)));
							break;
						}
					}
				}
			}
		}
	}
}

/*				INVENTORY MANAGER				*/
int32 URPGGameInstance::GetGold()
{
	return Gold;
}

void URPGGameInstance::SetGold(int32 InGold)
{
	Gold = InGold;
}


TArray<FItemDataStruct> URPGGameInstance::GetInventory()
{
	return Inventory;
}

void URPGGameInstance::SetInventory(TArray<FItemDataStruct> InInventory)
{
	Inventory = InInventory;
}

/*				CHARACTERS MANAGER				*/
TArray<FPartySlotStruct> URPGGameInstance::GetParty()
{
	return Party;
}

void URPGGameInstance::SetParty(TArray<FPartySlotStruct> InParty)
{
	Party = InParty;
}

TMap<FName, FCharacterInfoStruct> URPGGameInstance::GetCharacters()
{
	return Characters;
}

void URPGGameInstance::SetCharacters(TMap<FName, FCharacterInfoStruct> InCharacters)
{
	Characters = InCharacters;
}

/*				TIMER				*/
FTimespan* URPGGameInstance::GetTimePlayed()
{
	return TimePlayed;
}

void URPGGameInstance::SetTimePlayed(FTimespan* InTimePlayed)
{
	TimePlayed = new FTimespan(*InTimePlayed);
}

void URPGGameInstance::AddTimePlayed(FTimespan* InTimePlayed)
{
	TimePlayed = new FTimespan(TimePlayed->GetTotalDays() + InTimePlayed->GetTotalDays(), TimePlayed->GetTotalHours() + InTimePlayed->GetTotalHours(), TimePlayed->GetTotalMinutes() + InTimePlayed->GetTotalMinutes(), TimePlayed->GetTotalSeconds() + InTimePlayed->GetTotalSeconds(), TimePlayed->GetTotalMicroseconds() + InTimePlayed->GetTotalMicroseconds());
}

void URPGGameInstance::UpdateTimePlayed()
{
	FTimespan* EndTime = new FTimespan(FDateTime::Now().GetTicks());

	AddTimePlayed(new FTimespan(EndTime->GetTotalDays() - StartTime->GetTotalDays(),
								EndTime->GetTotalHours() - StartTime->GetTotalHours(),
								EndTime->GetTotalMinutes() - StartTime->GetTotalMinutes(),
								EndTime->GetTotalSeconds() - StartTime->GetTotalSeconds(),
								EndTime->GetTotalMicroseconds() - StartTime->GetTotalMicroseconds()));

	StartTime = new FTimespan(FDateTime::Now().GetTicks());
}

/*				MAP INFO				*/
FName URPGGameInstance::GetWorldMapName()
{
	return WorldMapName;
}

void URPGGameInstance::SetWorldMapName(FName InWorldMapName)
{
	WorldMapName = InWorldMapName;
}

FName URPGGameInstance::GetWorldMapSpawnPointName()
{
	return WorldMapSpawnPointName;
}

void URPGGameInstance::SetWorldMapSpawnPointName(FName InWorldMapSpawnPointName)
{
	WorldMapSpawnPointName = InWorldMapSpawnPointName;
}

FName URPGGameInstance::GetBattleArenaName()
{
	return BattleArenaName;
}

void URPGGameInstance::SetBattleArenaName(FName InBattleArenaName)
{
	BattleArenaName = InBattleArenaName;
}

FText URPGGameInstance::GetAreaName()
{
	return AreaName;
}

void URPGGameInstance::SetAreaName(FText InAreaName)
{
	AreaName = InAreaName;
}

bool URPGGameInstance::GetBSpawningAfterBattle()
{
	return bSpawningAfterBattle;
}

void URPGGameInstance::SetBSpawningAfterBattle(bool InBSpawningAfterBattle)
{
	bSpawningAfterBattle = InBSpawningAfterBattle;
}

FTransform URPGGameInstance::GetWorldTransformBeforeBattle()
{
	return WorldTransformBeforeBattle;
}

void URPGGameInstance::SetWorldTransformBeforeBattle(FTransform InWorldTransformBeforeBattle)
{
	WorldTransformBeforeBattle = InWorldTransformBeforeBattle;
}

FRotator URPGGameInstance::GetCameraRotationBeforeBattle()
{
	return CameraRotationBeforeBattle;
}

void URPGGameInstance::SetCameraRotationBeforeBattle(FRotator InCameraRotationBeforeBattle)
{
	CameraRotationBeforeBattle = InCameraRotationBeforeBattle;
}

TMap<FName, FTransform> URPGGameInstance::GetEnemiesTransformsBeforeBattle()
{
	return EnemiesTransformsBeforeBattle;
}

void URPGGameInstance::SetEnemiesTransformsBeforeBattle(TMap<FName, FTransform> InEnemiesTransformsBeforeBattle)
{
	EnemiesTransformsBeforeBattle = InEnemiesTransformsBeforeBattle;
}

void URPGGameInstance::SetSavePointName(FName InSavePointName)
{
	SavePointName = InSavePointName;
}

/*				ENCOUNTERS				*/
TArray<FName> URPGGameInstance::GetPossibleEncounters()
{
	return PossibleEncounters;
}

void URPGGameInstance::SetPossibleEncounters(TArray<FName> InPossibleEncounters)
{
	PossibleEncounters = InPossibleEncounters;
}

TArray<FName> URPGGameInstance::GetPossibleBattleMaps()
{
	return PossibleBattleMaps;
}

void URPGGameInstance::SetPossibleBattleMaps(TArray<FName> InPossibleBattleMaps)
{
	PossibleBattleMaps = InPossibleBattleMaps;
}

bool URPGGameInstance::GetRandomEncounter()
{
	return bRandomEncounter;
}

void URPGGameInstance::SetRandomEncounter(bool InbRandomEncounter)
{
	bRandomEncounter = InbRandomEncounter;
}

TMap<int32, FName> URPGGameInstance::GetEncounteredEnemies()
{
	return EncounteredEnemies;
}

void URPGGameInstance::SetEncounteredEnemies(TMap<int32, FName> InEncounteredEnemies)
{
	EncounteredEnemies = InEncounteredEnemies;
}

/*				World Managment				*/
TMap<FName, bool> URPGGameInstance::GetInteractedObjects()
{
	return InteractedObjects;
}

void URPGGameInstance::SetInteractedObjects(TMap<FName, bool> InInteractedObject)
{
	InteractedObjects = InInteractedObject;
}

TMap<FName, bool> URPGGameInstance::GetBattledEnemies()
{
	return BattledEnemies;
}

void URPGGameInstance::SetBattledEnemies(TMap<FName, bool> InBattledEnemies)
{
	BattledEnemies = InBattledEnemies;
}