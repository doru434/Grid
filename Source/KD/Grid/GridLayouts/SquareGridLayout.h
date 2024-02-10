#pragma once

#include "CoreMinimal.h"
#include "BaseGridLayout.h"
#include "SquareGridLayout.generated.h"

/**
 * @brief 
 */
UCLASS()
class KD_API USquareGridLayout : public UBaseGridLayout
{
	GENERATED_BODY()

	USquareGridLayout();
public:
	virtual bool GenerateGrid(OUT FGridData& InGridData) override;
	virtual TOptional<FTileData> GetTileAtLocation(const FGridData& InGridData, const FVector& Location) const override;
	
	float OffsetForGridCenter;
	float Offset;
};
