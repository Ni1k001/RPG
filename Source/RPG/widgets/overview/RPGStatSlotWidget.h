// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "RPG/enums/RPGStatTypeEnum.h"

#include "RPGStatSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URPGStatSlotWidget : public UUserWidget
{
	GENERATED_BODY()

	void NativePreConstruct();
	
public:
	UPROPERTY(BlueprintReadWrite)
		StatsEnum AssignedStatType;

	UPROPERTY(BlueprintReadWrite)
		int32 FontSize;

	UPROPERTY(BlueprintReadWrite)
		bool bIsComparisonEnabled;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_StatName;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_StatValue;

	UPROPERTY(meta = (BindWidget))
		class UHorizontalBox* HorizontalBox_Change;

	UPROPERTY(meta = (BindWidget))
		class UImage* Image_ComparisonArrow;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_NewValue;

	UPROPERTY(meta = (BindWidget))
		class UImage* Image_Arrow;

	UFUNCTION(BlueprintNativeEvent)
		void SetComparisonPartToHigher(float InValue);

	UFUNCTION(BlueprintNativeEvent)
		void SetComparisonPartToLower(float InValue);

	UFUNCTION(BlueprintNativeEvent)
		void SetComparisonPartToEqual(float InValue);
};
