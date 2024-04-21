// Fill out your copyright notice in the Description page of Project Settings.


#include "GridTypes.h"

FTileData::FTileData() :
	TilePosition(FVector::ZeroVector)
	, ID(-1)
	, TileDataAsset(nullptr)
{}

FTileData::FTileData(const FVector& InTilePosition, const uint32 InID) :
	TilePosition(InTilePosition)
	, ID(InID)
	, TileDataAsset(nullptr)
{}

FGridRow::FGridRow()
{}

FGridData::FGridData():
	  GridSize(10)
	, TileSize(10.f)
	, bFitToParent(true)
	, ParentRoot(FVector(TileSize * 0.5f, TileSize * 0.5f, 0))
	, GridRoot(FVector::ZeroVector)
	, HalfParentSize(FVector::ZeroVector)
{}

void FGridData::SetSize(uint32 InSize)
{
	GridSize = InSize;
	GridSizeChangedDelegate.ExecuteIfBound();
}
