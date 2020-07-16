// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGDynamicCameraManagerComponent.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
URPGDynamicCameraManagerComponent::URPGDynamicCameraManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URPGDynamicCameraManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<ARPGDynamicCameraPath> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		DynamicCameraPaths.Add(ActorItr->GetPathID(), *ActorItr);
	}

	FTransform Transform = FTransform(FRotator(0.f, 0.f, 0.f), FVector(0.f, 0.f, 0.f), FVector(1.f, 1.f, 1.f));
	ACameraActor* CameraActor = Cast<ACameraActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, ACameraActor::StaticClass(), Transform));

	if (CameraActor)
	{
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTargetWithBlend(CameraActor);

		UGameplayStatics::FinishSpawningActor(CameraActor, Transform);
	}

	if (bUseAutoCameraManagement)
	{
		SetNewDynamicPath(DefaultPathID, true, true, false, FVector(0.f, 0.f, 0.f));
	}
}


// Called every frame
void URPGDynamicCameraManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ActiveCameraPath->IsValidLowLevel())
	{
		if (PathDistance >= ActiveCameraPath->GetSpline()->GetSplineLength() && bIsLoopEnabled)
			PathDistance = 0.f;

		PathDistance += Speed * UGameplayStatics::GetWorldDeltaSeconds(GetWorld());

		UpdateCameraLocationAndRotation(PathDistance);
	}
}

void URPGDynamicCameraManagerComponent::SetNewDynamicPath(FName InPathID, bool InBRandomStartDistance, bool InBLoop, bool InBUpdatePathLocation, FVector InNewLocation)
{
	bIsLoopEnabled = InBLoop;

	ARPGDynamicCameraPath* Path = DynamicCameraPaths.FindRef(InPathID);

	if (Path)
	{
		ActiveCameraPath = Path;

		PathDistance = UKismetMathLibrary::SelectFloat(UKismetMathLibrary::RandomFloatInRange(0.f, 0.8f) * ActiveCameraPath->GetSpline()->GetSplineLength(), 0.f, InBRandomStartDistance);
	
		if (InBUpdatePathLocation)
		{
			ActiveCameraPath->SetActorLocation(InNewLocation);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Couldn't find camera path with ID: %s"), *InPathID.ToString());
	}
}

void URPGDynamicCameraManagerComponent::UpdateCameraLocationAndRotation(float InPathTime)
{

}