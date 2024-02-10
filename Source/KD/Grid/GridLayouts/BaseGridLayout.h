// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KD/Grid/GridTypes.h"
#include "UObject/Object.h"
#include "BaseGridLayout.generated.h"


UCLASS(Abstract, EditInlineNew)
class KD_API UBaseGridLayout : public UObject
{
	GENERATED_BODY()

public:
	virtual bool GenerateGrid(OUT FGridData& InGridData);
	virtual TOptional<FTileData> GetTileAtLocation(const FGridData& InGridData, const FVector& Location) const;
};
