// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "KD/Grid/GridTypes.h"
#include "BaseHUD.generated.h"

enum class ETooltipType : uint8;
class UTooltipWidget;
class UBaseTooltipDataAsset;

UCLASS()
class KD_API ABaseHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;
	void UpdateTooltipWidget(bool bShow, const FTileData& TileData);

	UFUNCTION(BlueprintCallable)
	void DrawTooltipWidget(const bool bShow);

	UFUNCTION(BlueprintCallable)
	void UpdateTooltipWidget(UBaseTooltipDataAsset* BaseTooltipDataAsset);

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UTooltipWidget> TooltipWidgetClass;

	UPROPERTY()
	TWeakObjectPtr<UTooltipWidget> TooltipWidget;


	void InitializeHUD();

	void InitializeTooltipWidget();

	virtual void BeginPlay() override;
};
