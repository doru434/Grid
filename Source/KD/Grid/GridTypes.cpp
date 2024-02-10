// Fill out your copyright notice in the Description page of Project Settings.


#include "GridTypes.h"

FTileData::FTileData():
	 TilePosition(FVector::ZeroVector)
{}

FTileData::FTileData(const FVector& InTilePosition)
{
	TilePosition=InTilePosition;
}

FGridRow::FGridRow()
{}

FGridData::FGridData():
	  GridSize(10)
	, TileSize(10.f)
	, bFitToParent(true)
	, ParentRoot(FVector(TileSize/2.f, TileSize/2.f, 0))
	, GridRoot(FVector::ZeroVector)
	, HalfParentSize(FVector::ZeroVector)
{}

void FGridData::SetSize(uint32 InSize)
{
	GridSize = InSize;
	GridSizeChangedDelegate.ExecuteIfBound();
}
