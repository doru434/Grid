// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Materials/MaterialInterface.h"
#include "KDSettings.generated.h"

/**
 * 
 */
UCLASS(config=Game, defaultconfig, meta=(DisplayName="KD"))
class KD_API UKDSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, config, Category = "KD", meta = (ToolTip = "DefaultCharacterSelectionDecalMaterial"))
	FVector DefaultCharacterSelectionDecalSize;

	UPROPERTY(EditAnywhere, config, Category = "KD", meta = (ToolTip = "DefaultCharacterSelectionDecalMaterial"))
	TSoftObjectPtr<UMaterialInterface> DefaultCharacterSelectionDecalMaterial;
	
	static UKDSettings* Get() { return CastChecked<UKDSettings>(UKDSettings::StaticClass()->GetDefaultObject()); }
};
