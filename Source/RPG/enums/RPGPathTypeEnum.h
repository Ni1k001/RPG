// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "RPGPathTypeEnum.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class PathTypeEnum : uint8
{
	ELoop				UMETA(DisplayName = "Loop"),
	ESpiral				UMETA(DisplayName = "Spiral"),
	EStatic				UMETA(DisplayName = "Static"),
	EManual				UMETA(DisplayName = "Manual"),
};
