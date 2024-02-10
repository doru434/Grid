#pragma once

#include "CoreMinimal.h"
#include "IntVectorTypes.h"
#include "GridTypes.generated.h"

DECLARE_DYNAMIC_DELEGATE(FGridSizeChangedDelegate);


USTRUCT()
struct FTileData
{
	GENERATED_BODY()
	
	FTileData();

	explicit FTileData(const FVector& InTilePosition);

	UPROPERTY(VisibleAnywhere)
	FVector TilePosition;
};


USTRUCT()
struct FGridRow
{
	GENERATED_BODY()
	
	FGridRow();
	
	UPROPERTY(VisibleAnywhere)
	TArray<FTileData> Tile;

	bool IsIndexValid(const int32 Index) const
	{
		return Tile.IsValidIndex(Index);
	}
};


USTRUCT()
struct FGridData
{
	GENERATED_BODY()

	UPROPERTY()
	FGridSizeChangedDelegate GridSizeChangedDelegate;
	
	FGridData();

	void SetSize(uint32 InSize);

	UPROPERTY(VisibleAnywhere)
	TArray<FGridRow> Grid;
	
	UPROPERTY(EditAnywhere)
	int GridSize;
	
	UPROPERTY(EditAnywhere)
	float TileSize;
	
	UPROPERTY(EditAnywhere)
	bool bFitToParent;
	
	UPROPERTY(EditAnywhere, meta = (EditCondition ="bFitToParent == true"))
	FVector ParentRoot;

	UPROPERTY()
	FVector GridRoot;
	
	UPROPERTY()
	FVector HalfParentSize;

	bool IsIndexValid(const UE::Geometry::FVector2i& Index) const
	{
		return Grid.IsValidIndex(Index.X) && Grid[Index.X].IsIndexValid(Index.Y);
	}
};