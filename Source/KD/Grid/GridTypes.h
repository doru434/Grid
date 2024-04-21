#pragma once

#include "CoreMinimal.h"
#include "IntVectorTypes.h"
#include "Engine/DataAsset.h"
#include "KD/Interaction/InteractionTypes.h"
#include "GridTypes.generated.h"


class UTilePayloadInteractionDataAsset;
DECLARE_DYNAMIC_DELEGATE(FGridSizeChangedDelegate);

UENUM(BlueprintType)
enum class ETileType : uint8
{
	None,
	Grassland,
	Desert,
	Forest
};

UCLASS()
class UTileDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UTilePayloadInteractionDataAsset* GetTilePayloadInteractionDataAsset() const { return TilePayloadInteractionDataAsset; }

protected:
	UPROPERTY()
	ETileType TileType = ETileType::None;

	UPROPERTY()
	TObjectPtr<UTilePayloadInteractionDataAsset> TilePayloadInteractionDataAsset = nullptr;;
};

UCLASS()
class UTilePayloadInteractionDataAsset : public UPayloadInteractionData
{
	GENERATED_BODY()

// public:
// 	bool operator==(const UTilePayloadInteractionDataAsset& Other)
// 	{
// 		return IsEqual(&Other);
// 	}
// 
// protected:
// 	virtual bool IsEqual(const UTilePayloadInteractionDataAsset* Other) const { return true; }


};

USTRUCT()
struct FTileData
{
	GENERATED_BODY()
	
	FTileData();

	explicit FTileData(const FVector& InTilePosition, const uint32 InID);

	UPROPERTY(VisibleAnywhere)
	FVector TilePosition;

	UPROPERTY(VisibleAnywhere)
	int32 ID;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTileDataAsset> TileDataAsset;

	UTilePayloadInteractionDataAsset* GetTilePayloadInteractionDataAssett() const { return TileDataAsset->GetTilePayloadInteractionDataAsset(); }
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