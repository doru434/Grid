#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UITypes.generated.h"

UCLASS(Blueprintable, Abstract)
class UBaseTooltipDataAsset : public UDataAsset
{
	GENERATED_BODY()


};

UENUM(BlueprintType)
enum class ETooltipType : uint8
{
	None,
	GridTile,
	Default,
	Unit
};