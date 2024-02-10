// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGridLayout.h"

bool UBaseGridLayout::GenerateGrid(FGridData& InGridData)
{
	return true;
}

TOptional<FTileData> UBaseGridLayout::GetTileAtLocation(const FGridData& InGridData, const FVector& Location) const
{
	TOptional<FTileData> TileData;
	return TileData;
}
 