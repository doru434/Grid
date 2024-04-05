// Fill out your copyright notice in the Description page of Project Settings.


#include "KD/UI/WIdgets/ToolTipWidget.h"
#include "KD/UI/UITypes.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "KD/Core/KDTypes.h"

UTooltipWidget::UTooltipWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void UTooltipWidget::Update(ETooltipType TooltipType, UBaseTooltipDataAsset* BaseTooltipDataAsset)
{
	switch (TooltipType)
	{
	case ETooltipType::None:
		break;
	case ETooltipType::Tile:
		break;
	case ETooltipType::Unit:
		break;
	}
}

void UTooltipWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (IsInViewport())
	{
		// to be certain that GetDesiredSize() will return correct value
		ForceLayoutPrepass();
		// move to mouse position
		const FVector2D& MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
		const FVector2D WidgetSize = GetDesiredSize();
		FGeometry WidgetGeometry = UWidgetLayoutLibrary::GetViewportWidgetGeometry(this);

		FVector2D NewWidgetPostion = FVector2D(FMath::Clamp(MousePosition.X, 0.0f, WidgetGeometry.GetLocalSize().X), FMath::Clamp(MousePosition.Y, 0.0f, WidgetGeometry.GetLocalSize().Y));

		Allign(NewWidgetPostion, WidgetSize, WidgetGeometry.GetLocalSize());

		SetPositionInViewport(NewWidgetPostion, false);

		if (GEngine && KD_GRAPHIC_LOG)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, FString::Printf(TEXT("MousePosition_ X: %f, Y: %f"), MousePosition.X, MousePosition.Y));
			GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, FString::Printf(TEXT("NewWidgetPostion_ X: %f, Y: %f"), NewWidgetPostion.X, NewWidgetPostion.Y));
			GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, FString::Printf(TEXT("WidgetSize X: %f, Y: %f"), WidgetSize.X, WidgetSize.Y));

			GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Cyan, FString::Printf(TEXT("FGeometry.GetLocalSize_ X: %f, Y: %f"), WidgetGeometry.GetLocalSize().X, WidgetGeometry.GetLocalSize().Y));
		}
	}
}

void UTooltipWidget::Allign(OUT FVector2D& WidgetPosition, const FVector2D& WidgetSize, const FVector2f& ViewportSize)
{
	AllignVertically(WidgetPosition, WidgetSize, ViewportSize);
	AllignHorizontally(WidgetPosition, WidgetSize, ViewportSize);
}

void UTooltipWidget::AllignVertically(OUT FVector2D& WidgetPosition, const FVector2D& WidgetSize, const FVector2f& ViewportSize)
{
	const double Diff = ViewportSize.X - (WidgetPosition.X + WidgetSize.X);

	if (Diff < 0.0)
	{
		WidgetPosition.X += Diff;
	}
}

void UTooltipWidget::AllignHorizontally(OUT FVector2D& WidgetPosition, const FVector2D& WidgetSize, const FVector2f& ViewportSize)
{
	const double Diff = ViewportSize.Y - (WidgetPosition.Y + WidgetSize.Y);

	if (Diff < 0.0)
	{
		WidgetPosition.Y += Diff;
	}
}
