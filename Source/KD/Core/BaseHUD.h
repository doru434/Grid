// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseHUD.generated.h"

class UTooltipWidget;
class UBaseTooltipDataAsset;

UCLASS()
class KD_API ABaseHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;

	UFUNCTION(BlueprintCallable)
	void DrawTooltipWidget(const bool bShow);

	UFUNCTION(BlueprintCallable)
	void UpdateTooltipWidget(ETooltipType TooltipType, UBaseTooltipDataAsset* BaseTooltipDataAsset);

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UTooltipWidget> TooltipWidgetClass;

	UPROPERTY()
	TWeakObjectPtr<UTooltipWidget> TooltipWidget;


	void InitializeHUD();

	void InitializeTooltipWidget();

	virtual void BeginPlay() override;
};
