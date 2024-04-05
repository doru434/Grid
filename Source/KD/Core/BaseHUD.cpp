// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHUD.h"
#include "KD/UI/UITypes.h"
#include "KD/UI/Widgets/ToolTipWidget.h"

void ABaseHUD::DrawHUD()
{
	Super::DrawHUD();
}

void ABaseHUD::DrawTooltipWidget(const bool bShow)
{

	if (TooltipWidgetClass)
	{
		UTooltipWidget* TooltipWidgetRaw = TooltipWidget.Get();
		ensure(TooltipWidgetRaw);

		if (TooltipWidgetRaw)
		{
			bShow ? TooltipWidgetRaw->SetVisibility(ESlateVisibility::Visible) : TooltipWidgetRaw->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void ABaseHUD::UpdateTooltipWidget(ETooltipType TooltipType, UBaseTooltipDataAsset* BaseTooltipDataAsset)
{
	UTooltipWidget* TooltipWidgetRaw = TooltipWidget.Get();
	ensure(TooltipWidgetRaw);
	if (TooltipWidgetRaw)
	{
		TooltipWidgetRaw->Update(TooltipType, BaseTooltipDataAsset);
	}
}

void ABaseHUD::InitializeHUD()
{
	InitializeTooltipWidget();
}

void ABaseHUD::InitializeTooltipWidget()
{
	check( !TooltipWidget.Get());

	UTooltipWidget* TooltipWidgetRaw = CreateWidget<UTooltipWidget>(GetWorld(), TooltipWidgetClass);
	TooltipWidgetRaw->AddToViewport();
	TooltipWidgetRaw->SetVisibility(ESlateVisibility::Collapsed);

	TooltipWidget = MakeWeakObjectPtr(TooltipWidgetRaw);
}

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();

	InitializeHUD();
}
