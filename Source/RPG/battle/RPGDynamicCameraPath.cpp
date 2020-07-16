// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGDynamicCameraPath.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ARPGDynamicCameraPath::ARPGDynamicCameraPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	switch (PathType)
	{
	case PathTypeEnum::ELoop:
		SplineComponent->SetClosedLoop(bIsLoopClosed);
		SplineComponent->ClearSplinePoints();

		for (int i = 0; i < PointsAmount; i++)
		{
			float v = i * (360.f / (float)PointsAmount);
			
			SplineComponent->AddSplinePoint(FVector(LoopRadius * UKismetMathLibrary::DegCos(v), LoopRadius * UKismetMathLibrary::DegSin(v), 0.f), ESplineCoordinateSpace::Local);
		}
		break;
	case PathTypeEnum::ESpiral:
		SplineComponent->SetClosedLoop(false);
		SplineComponent->ClearSplinePoints();

		for (int i = 0; i < UKismetMathLibrary::Round(PointsAmount * SpiralLength); i++)
		{
			float v = i * (360.f / (float)PointsAmount);

			SplineComponent->AddSplinePoint(FVector(LoopRadius * UKismetMathLibrary::DegCos(v), LoopRadius * UKismetMathLibrary::DegSin(v), (float)i / (float)PointsAmount * SpiralOffset), ESplineCoordinateSpace::Local);
		}
		break;
	default:
		break;
	}

	/*for (int i = 0; i < SplineComponent->GetNumberOfSplinePoints() - 1; i++) //blablabla
	{
		SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);
		SplineComponent->GetRotationAtSplinePoint(i, ESplineCoordinateSpace::Local);
	}*/

	SplineComponent->SetRelativeRotation(PathInitialRotation);

	Camera->SetRelativeLocation(SplineComponent->GetLocationAtTime(PreviewTime, ESplineCoordinateSpace::Local));
	Camera->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(Camera->GetComponentLocation(), GetActorLocation() + CameraFocusPoint));
}

// Called when the game starts or when spawned
void ARPGDynamicCameraPath::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARPGDynamicCameraPath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

USplineComponent* ARPGDynamicCameraPath::GetSpline()
{
	return SplineComponent;
}

FName ARPGDynamicCameraPath::GetPathID()
{
	return PathID;
}

PathTypeEnum ARPGDynamicCameraPath::GetPathType()
{
	return PathType;
}

FVector ARPGDynamicCameraPath::GetCameraFoucsPoint()
{
	return CameraFocusPoint;
}

FRotator ARPGDynamicCameraPath::GetPathInitialRotation()
{
	return PathInitialRotation;
}

float ARPGDynamicCameraPath::GetLoopRadius()
{
	return LoopRadius;
}

bool ARPGDynamicCameraPath::GetBIsLoopClosed()
{
	return bIsLoopClosed;
}

float ARPGDynamicCameraPath::GetSpiralRadius()
{
	return SpiralRadius;
}

float ARPGDynamicCameraPath::GetSpiralLength()
{
	return SpiralLength;
}

float ARPGDynamicCameraPath::GetSpiralOffset()
{
	return SpiralOffset;
}

float ARPGDynamicCameraPath::GetPreviewTime()
{
	return PreviewTime;
}

FVector ARPGDynamicCameraPath::GetPathLocationAtDistance(float Time)
{
	return SplineComponent->GetLocationAtDistanceAlongSpline(Time, ESplineCoordinateSpace::World);
}

FVector ARPGDynamicCameraPath::GetCameraFocusPoint()
{
	return GetActorLocation() + CameraFocusPoint;
}