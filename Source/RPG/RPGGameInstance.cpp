// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameInstance.h"
#include "RPGSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine.h"

/*				DEFAULT				*/
void URPGGameInstance::Init()
{
	UGameInstance::Init();
	TimePlayed = new FTimespan(0,0,0,0,0);
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

	/*				SAVED DATA				*/
void URPGGameInstance::SaveData(FString SaveSlotName, int32 UserIndex, FName SavePoint)
{
	UpdateTimePlayed();

	URPGSaveGame* SaveGameInstance = Cast<URPGSaveGame>(UGameplayStatics::CreateSaveGameObject(URPGSaveGame::StaticClass()));

	SaveGameInstance->Gold = GetGold();
	SaveGameInstance->Party = GetParty();
	SaveGameInstance->Characters = GetCharacters();
	SaveGameInstance->TimePlayed = *GetTimePlayed();
	SaveGameInstance->WorldMapName = GetWorldMapName();
	SaveGameInstance->SavePoint = SavePoint;
	SaveGameInstance->bRandomEncounter = GetRandomEncounter();
	SaveGameInstance->InteractedObjects = GetInteractedObjects();
	SaveGameInstance->BattledEnemies = GetBattledEnemies();

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveSlotName, (uint32)UserIndex);

	UE_LOG(LogTemp, Warning, TEXT("SAVED GOLD: %d"), GetGold());
	UE_LOG(LogTemp, Warning, TEXT("SAVED TIME: %d:%d:%d"), FMath::FloorToInt(GetTimePlayed()->GetTotalHours()), GetTimePlayed()->GetMinutes(), GetTimePlayed()->GetSeconds());
	UE_LOG(LogTemp, Warning, TEXT("CURRENT TIME: %d:%d:%d"), FMath::FloorToInt(SaveGameInstance->TimePlayed.GetTotalHours()), SaveGameInstance->TimePlayed.GetMinutes(), SaveGameInstance->TimePlayed.GetSeconds());
}

void URPGGameInstance::LoadData(FString SaveSlotName, int32 UserIndex, FName& SavePoint)
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
		SavePoint = LoadGameInstance->SavePoint;

		StartTime = new FTimespan(FDateTime::Now().GetTicks());

		UE_LOG(LogTemp, Warning, TEXT("LOADED GOLD: %d"), GetGold());
		UE_LOG(LogTemp, Warning, TEXT("SAVED TIME: %d:%d:%d"), FMath::FloorToInt(GetTimePlayed()->GetTotalHours()), GetTimePlayed()->GetMinutes(), GetTimePlayed()->GetSeconds());
		UE_LOG(LogTemp, Warning, TEXT("CURRENT TIME: %d:%d:%d"), FMath::FloorToInt(LoadGameInstance->TimePlayed.GetTotalHours()), LoadGameInstance->TimePlayed.GetMinutes(), LoadGameInstance->TimePlayed.GetSeconds());
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

//UFUNCTION
//UFUNCTION

/*				CHARACTERS MANAGER				*/
TArray<FCharacterInfoStruct> URPGGameInstance::GetParty()
{
	return Party;
}

UFUNCTION(BlueprintSetter, Category = "CharacterManager")
void URPGGameInstance::SetParty(TArray<FCharacterInfoStruct> InParty)
{
	Party = InParty;
}

void URPGGameInstance::ChangePartyMember(int32 Index, FCharacterInfoStruct Character)
{
	Party[Index] = Character;
}

TMap<FName, FCharacterInfoStruct> URPGGameInstance::GetCharacters()
{
	return Characters;
}

void URPGGameInstance::SetCharacters(TMap<FName, FCharacterInfoStruct> InCharacters)
{
	Characters = InCharacters;
}

void URPGGameInstance::SetCharacter(FCharacterInfoStruct InCharacter, int32 InIndex)
{
	Characters.FindOrAdd(InCharacter.CharacterName, InCharacter);
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