// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGDamagePopUp.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ARPGDamagePopUp::ARPGDamagePopUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TextComponent = CreateEditorOnlyDefaultSubobject<UTextRenderComponent>(TEXT("Text"));
	if (TextComponent)
	{
		TextComponent->SetupAttachment(RootComponent);
		TextComponent->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));


		TextComponent->Text = FText::FromString("Text");

		TextComponent->VerticalAlignment = EVerticalTextAligment::EVRTA_TextCenter;
		TextComponent->HorizontalAlignment = EHorizTextAligment::EHTA_Center;

		TextComponent->SetTextRenderColor(FColor::White);
	}

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = TextComponent;
	ProjectileMovement->InitialSpeed = 500.f;
	ProjectileMovement->MaxSpeed = 0.f;
	ProjectileMovement->bRotationFollowsVelocity = false;
	ProjectileMovement->bInitialVelocityInLocalSpace = true;
	ProjectileMovement->ProjectileGravityScale = 1.f;

	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->bBounceAngleAffectsFriction = false;
}

// Called when the game starts or when spawned
void ARPGDamagePopUp::BeginPlay()
{
	Super::BeginPlay();

	while (!CameraReference->IsValidLowLevel())
	{
		CameraReference = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewTarget();
	}
}

void ARPGDamagePopUp::Init()
{
	if (bIsReducingInitiative)
	{
		TextComponent->Text = FText::FromString("- " + FString::SanitizeFloat(trunc(Value)));
		TextComponent->SetTextRenderColor(FColor::White);
		ProjectileMovement->Velocity = FVector(0.f, 0.f, 2.f);
	}
	else if (bIsHealing)
	{
		TextComponent->Text = FText::FromString("+ " + FString::SanitizeFloat(trunc(Value)));
		ProjectileMovement->Velocity = FVector(0.f, 0.f, 2.f);

		if (bIsRestoringMP)
			TextComponent->SetTextRenderColor(FColor::Blue);
		else
			TextComponent->SetTextRenderColor(FColor::Green);
	}
	else
	{
		TextComponent->Text = FText::FromString("- " + FString::SanitizeFloat(trunc(Value)));
		ProjectileMovement->Velocity = FVector(FMath::RandRange(-.1f, .1f), FMath::RandRange(-.1f, .1f), 1.f);

		if (bIsCritical)
		{
			TextComponent->SetTextRenderColor(FColor::Red);
			TextComponent->SetWorldScale3D(FVector(1.5f, 1.5f, 1.5f));
		}
	}
}

// Called every frame
void ARPGDamagePopUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CameraReference->IsValidLowLevel())
	{
		SetActorRotation(FRotator(UKismetMathLibrary::FindLookAtRotation(CameraReference->GetActorLocation(), GetActorLocation())));
	}
}