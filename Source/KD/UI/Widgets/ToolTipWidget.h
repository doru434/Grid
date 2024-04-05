// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BaseCommonWidget.h"
#include "TooltipWidget.generated.h"

/**
 * 
 */
UCLASS()
class KD_API UTooltipWidget : public UBaseCommonWidget
{
	GENERATED_BODY()
	
public:
	UTooltipWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void Update(ETooltipType TooltipType, UBaseTooltipDataAsset* BaseTooltipDataAsset);

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void Allign(OUT FVector2D& WidgetPosition, const FVector2D& WidgetSize, const FVector2f& ViewportSize);

	void AllignVertically(OUT FVector2D& WidgetPosition, const FVector2D& WidgetSize, const FVector2f& ViewportSize);
	void AllignHorizontally(OUT FVector2D& WidgetPosition, const FVector2D& WidgetSize, const FVector2f& ViewportSize);
};
