// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGCharactersManagerComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
URPGCharactersManagerComponent::URPGCharactersManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URPGCharactersManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	while (!GameInstance)
	{
		GameInstance = Cast<URPGGameInstance>(GetWorld()->GetGameInstance());
	}
}


// Called every frame
void URPGCharactersManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

