// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGBattleCharacterStatsComponent.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/KismetMathLibrary.h"

#include "RPG/RPGGameInstance.h"

#include "RPG/battle/RPGBattleCharacter.h"

#include "RPG/components/RPGBattleManagerComponent.h"

#include "RPG/interfaces/RPGBattleCommunicationInterface.h"

#include "RPG/widgets/battle/RPGBattleCharacterSlotWidget.h"

// Sets default values for this component's properties
URPGBattleCharacterStatsComponent::URPGBattleCharacterStatsComponent(const FObjectInitializer& ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<URPGBattleCharacterSlotWidget> CharacterBattleSlotBPClass(TEXT("/Game/Widgets/Battle/BattleCharacterSlot"));

	if (CharacterBattleSlotBPClass.Class != nullptr)
		CharacterBattleSlotClass = CharacterBattleSlotBPClass.Class;
}


// Called when the game starts
void URPGBattleCharacterStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	while (!GameInstance)
	{
		GameInstance = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());
	}
}


// Called every frame
void URPGBattleCharacterStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FName URPGBattleCharacterStatsComponent::GetHardcodedName()
{
	return Name;
}

FText URPGBattleCharacterStatsComponent::GetDisplayName()
{
	return DisplayName;
}

bool URPGBattleCharacterStatsComponent::GetBIsDefending()
{
	return bIsDefending;
}

void URPGBattleCharacterStatsComponent::SetBIsDefending(bool InBIsDefending)
{
	bIsDefending = InBIsDefending;
}

TMap<StatsEnum, float> URPGBattleCharacterStatsComponent::GetStats()
{
	return Stats;
}

void URPGBattleCharacterStatsComponent::SetStats(TMap<StatsEnum, float> InStats)
{
	Stats = InStats;
}

TMap<DerivedStatsEnum, float> URPGBattleCharacterStatsComponent::GetDerivedStats()
{
	return DerivedStats;
}

void URPGBattleCharacterStatsComponent::SetDerivedStats(TMap<DerivedStatsEnum, float> InDerivedStats)
{
	DerivedStats = InDerivedStats;
}

float URPGBattleCharacterStatsComponent::GetCurrentHP()
{
	return CurrentHP;
}

void URPGBattleCharacterStatsComponent::SetCurrentHP(float InAmount)
{
	CurrentHP = InAmount;
}

float URPGBattleCharacterStatsComponent::GetCurrentMP()
{
	return CurrentMP;
}

void URPGBattleCharacterStatsComponent::SetCurrentMP(float InAmount)
{
	CurrentMP = InAmount;
}

float URPGBattleCharacterStatsComponent::GetCurrentInitiative()
{
	return CurrentInitiative;
}

URPGBattleCharacterSlotWidget* URPGBattleCharacterStatsComponent::GetBattleCharacterSlotRef()
{
	return BattleCharacterSlotRef;
}

void URPGBattleCharacterStatsComponent::SetBattleCharacterSlotRef(URPGBattleCharacterSlotWidget* InBattleCharacterSlotRef)
{
	BattleCharacterSlotRef = InBattleCharacterSlotRef;
}

URPGBattleManagerComponent* URPGBattleCharacterStatsComponent::GetBattleManagerRef()
{
	return BattleManagerReference;
}

void URPGBattleCharacterStatsComponent::SetBattleManagerRef(URPGBattleManagerComponent* InBattleManagerReference)
{
	BattleManagerReference = InBattleManagerReference;
}

ActionTypeEnum URPGBattleCharacterStatsComponent::GetSelectedActionType()
{
	return SelectedActionType;
}

void URPGBattleCharacterStatsComponent::SetSelectedActonType(ActionTypeEnum InSelectedActionType)
{
	SelectedActionType = InSelectedActionType;
}

TArray<ARPGBattleCharacter*> URPGBattleCharacterStatsComponent::GetTargetedCharacters()
{
	return TargetedCharacters;
}

void URPGBattleCharacterStatsComponent::SetTargetedCharacters(TArray<ARPGBattleCharacter*> InTargetedCharacters)
{
	TargetedCharacters = InTargetedCharacters;
}

/*				Initialization				*/
void URPGBattleCharacterStatsComponent::SetCharacterData(FText InDisplayName, TMap<StatsEnum, float> InStats, TMap<DerivedStatsEnum, float> InDerivedStats, float InCurrentHP, float InCurrentMP)
{
	DisplayName = InDisplayName;
	Stats = InStats;
	DerivedStats = InDerivedStats;
	CurrentHP = InCurrentHP;
	CurrentMP = InCurrentMP;
}

void URPGBattleCharacterStatsComponent::CreateCharacterBattleSlot()
{
	if (CharacterBattleSlotClass == nullptr)
		return;

	BattleCharacterSlotRef = CreateWidget<URPGBattleCharacterSlotWidget>(GetWorld(), CharacterBattleSlotClass);

	if (BattleCharacterSlotRef)
	{
		BattleCharacterSlotRef->UpdateCharacterDisplayName(DisplayName);
		RefreshHP();
		RefreshMP();
		RefreshInitiative();

		//UWidgetBlueprintLibrary::GetAllWidgetsOfClass
	}
}

	/*				Damage						*/
void URPGBattleCharacterStatsComponent::ReceiveDamage(float InDamage, float InCriticalRate, float InCriticalPower)
{
	if (CurrentHP > 0.f)
	{
		float Damage = InDamage;
		

		bool bIsCritical = UKismetMathLibrary::RandomBoolWithWeight(InCriticalRate / 100);

		if (bIsCritical)
			Damage = InDamage * (InCriticalPower / 100);

		Damage -= *DerivedStats.Find(DerivedStatsEnum::EDefense);

		Damage = FMath::TruncToInt(FMath::Clamp(CalculateDefendStanceDamageReduction(Damage), 1.f, 9999.f));

		CurrentHP = FMath::Clamp(CurrentHP - Damage, 0.f, *Stats.Find(StatsEnum::EHP));

		if (GetOwner()->GetClass()->ImplementsInterface(URPGBattleCommunicationInterface::StaticClass()))
		{
			IRPGBattleCommunicationInterface::Execute_OnDamageReceived(GetOwner(), Damage, bIsCritical);
		}
		//OnDamageReceived(GetOwner(), Damage, bIsCritical);

		RefreshHP();

		if (CurrentHP == 0.f)
		{
			if (GetOwner()->GetClass()->ImplementsInterface(URPGBattleCommunicationInterface::StaticClass()))
			{
				IRPGBattleCommunicationInterface::Execute_OnDeath(GetOwner());
			}
			//OnDeath(GetOwner());
		}
	}
}

float URPGBattleCharacterStatsComponent::CalculateDefendStanceDamageReduction(float InDamage)
{
	if (bIsDefending)
	{
		return InDamage * 0.7f;
	}

	return InDamage;
}

void URPGBattleCharacterStatsComponent::ReduceInitiative(float InAmount)
{
	if (BattleManagerReference)
	{
		CurrentInitiative = FMath::Clamp(CurrentInitiative - InAmount, 0.f, BattleManagerReference->GetRequiredInitiative());
	
		if (GetOwner()->GetClass()->ImplementsInterface(URPGBattleCommunicationInterface::StaticClass()))
		{
			IRPGBattleCommunicationInterface::Execute_OnInitiativeReduced(GetOwner(), InAmount);
		}
		//OnInitiativeReduced(GetOwner(), InAmount);

		RefreshInitiative();
	}
}

void URPGBattleCharacterStatsComponent::ReduceHP(float InAmount)
{
	CurrentHP -= InAmount;

	RefreshHP();
}

void URPGBattleCharacterStatsComponent::ReduceMP(float InAmount)
{
	CurrentMP -= InAmount;

	RefreshMP();
}

/*				Initiative					*/
void URPGBattleCharacterStatsComponent::RefreshInitiative()
{
	if (BattleManagerReference->IsValidLowLevel())
	{
		if (BattleCharacterSlotRef->IsValidLowLevel())
		{
			BattleCharacterSlotRef->UpdateInitiativeValue(CurrentInitiative, BattleManagerReference->GetRequiredInitiative());
		}
	}
}

void URPGBattleCharacterStatsComponent::AddInitiative(float InAmount)
{
	if (InAmount == 0)
		CurrentInitiative = FMath::Clamp(CurrentInitiative + *Stats.Find(StatsEnum::EInitiative), 0.f, 1000.f);
	else
		CurrentInitiative = FMath::Clamp(CurrentInitiative + InAmount, 0.f, 1000.f);

	RefreshInitiative();

}

void URPGBattleCharacterStatsComponent::RemoveInitiative(float InAmount)
{
	CurrentInitiative = FMath::Clamp(CurrentInitiative - InAmount, 0.f, 1000.f);

	RefreshInitiative();
}

/*				Recovery					*/
void URPGBattleCharacterStatsComponent::RefreshHP()
{
	if (BattleCharacterSlotRef->IsValidLowLevel())
	{
		BattleCharacterSlotRef->UpdateHealthValue(CurrentHP, *Stats.Find(StatsEnum::EHP));
	}
}

void URPGBattleCharacterStatsComponent::RefreshMP()
{
	if (BattleCharacterSlotRef->IsValidLowLevel())
	{
		BattleCharacterSlotRef->UpdateHealthValue(CurrentMP, *Stats.Find(StatsEnum::EMP));
	}
}

void URPGBattleCharacterStatsComponent::RecoverHP(float InAmount)
{
	CurrentHP = FMath::Clamp(CurrentHP + InAmount, 0.f, *Stats.Find(StatsEnum::EHP));

	RefreshHP();

	if (GetOwner()->GetClass()->ImplementsInterface(URPGBattleCommunicationInterface::StaticClass()))
	{
		IRPGBattleCommunicationInterface::Execute_OnHealed(GetOwner(), InAmount, false);
	}
	//OnHealed(GetOwner(), InAmount, false);
}

void URPGBattleCharacterStatsComponent::RecoverMP(float InAmount)
{
	CurrentMP = FMath::Clamp(CurrentMP + InAmount, 0.f, *Stats.Find(StatsEnum::EMP));

	RefreshMP();

	if (GetOwner()->GetClass()->ImplementsInterface(URPGBattleCommunicationInterface::StaticClass()))
	{
		IRPGBattleCommunicationInterface::Execute_OnHealed(GetOwner(), InAmount, true);
	}
	//OnHealed(GetOwner(), InAmount, true);
}

void URPGBattleCharacterStatsComponent::Resurrect(float InAmount)
{
	CurrentHP = FMath::Clamp(InAmount, 0.f, *Stats.Find(StatsEnum::EHP));

	RefreshHP();

	if (GetOwner()->GetClass()->ImplementsInterface(URPGBattleCommunicationInterface::StaticClass()))
	{
		IRPGBattleCommunicationInterface::Execute_OnResurrected(GetOwner(), InAmount);
	}
	//OnResurected(GetOwner());
}