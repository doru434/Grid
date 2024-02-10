// Fill out your copyright notice in the Description page of Project Settings.


#include "SquareGridLayout.h"

#include "IntVectorTypes.h"
#include "KD/Core/KDTypes.h"

USquareGridLayout::USquareGridLayout()
	: OffsetForGridCenter{0.f}
	, Offset{0.f}
{}

bool USquareGridLayout::GenerateGrid(FGridData& InGridData)
{
	Offset += InGridData.TileSize * 0.5f;
	if(InGridData.bFitToParent)
	{
		const double InvTileSize = 1.0/InGridData.TileSize;
		const double SizeX = InGridData.HalfParentSize.X * 2.0 * InvTileSize;
		const double SizeY = InGridData.HalfParentSize.Y * 2.0 * InvTileSize;

		for(int i=0; i < SizeX; ++i)
		{
			FGridRow NewRow;

			for(int j=0; j < SizeY; ++j)
			{
				FVector TilePosition{FVector::ZeroVector};
				TilePosition.X = (InGridData.TileSize * i) + Offset + InGridData.ParentRoot.X - InGridData.HalfParentSize.X;
				TilePosition.Y = (InGridData.TileSize * j) + Offset + InGridData.ParentRoot.Y - InGridData.HalfParentSize.Y;

				FTileData Tile(TilePosition);
				NewRow.Tile.Add(Tile);
				if( i == 0 && j == 0)
				{
					InGridData.GridRoot = TilePosition;
				}
			}
			InGridData.Grid.Add(NewRow);
		}
		return true;
	}
	else
	{
		OffsetForGridCenter = InGridData.GridSize * InGridData.TileSize * 0.5f;
		for(int i=0; i < InGridData.GridSize; ++i)
		{
			FGridRow NewRow;

			for(int j=0; j < InGridData.GridSize; ++j)
			{
				FVector TilePosition{FVector::ZeroVector};
				TilePosition.X = (InGridData.TileSize * i) + Offset + InGridData.ParentRoot.X - OffsetForGridCenter;
				TilePosition.Y = (InGridData.TileSize * j) + Offset + InGridData.ParentRoot.Y - OffsetForGridCenter;

				FTileData Tile(TilePosition);
				NewRow.Tile.Add(Tile);
			}
			InGridData.Grid.Add(NewRow);
		}
		return true;
	}
	return false;
}

TOptional<FTileData> USquareGridLayout::GetTileAtLocation(const FGridData& InGridData, const FVector& Location) const
{
	TOptional<FTileData> TileData;
	UE::Geometry::FVector2i Index = UE::Geometry::FVector2i::Zero();
	const float InvTileSize = 1.f / InGridData.TileSize;
	Index.X = FMath::FloorToInt((Location.X  - InGridData.GridRoot.X + OffsetForGridCenter + (InGridData.TileSize* 0.5f)) * InvTileSize);
	Index.Y = FMath::FloorToInt((Location.Y  - InGridData.GridRoot.Y + OffsetForGridCenter + (InGridData.TileSize* 0.5f)) * InvTileSize);

#if KD_LOG && WITH_EDITOR
	if(GEngine)
	{
		const FString OnScreenMessage = FString::Printf(TEXT("GetTileAtLocation: %f %f"), Index.X, Index.Y);
		GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Emerald, OnScreenMessage);
		const FString OnScreenMessage2 = FString::Printf(TEXT("Location: %f %f"), Location.X, Location.Y);
		GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Emerald, OnScreenMessage2);
	}
#endif
	
	if(InGridData.IsIndexValid(Index))
	{
		TileData = InGridData.Grid[Index.X].Tile[Index.Y];
	}

	return TileData;
}
