// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "PASettings.generated.h"

/**
 * 
 */
UCLASS(config=Game, defaultconfig, meta=(DisplayName="Grid"))
class KD_API UPASettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

// 	UPROPERTY(Config, EditAnywhere, Category = "Grid")
// 	float BaseDecalZSize;
// 
// 	UPROPERTY(Config, EditAnywhere, Category = "Grid")
// 	FRotator TopDownDecal;
// 
// 	UPROPERTY(Config, EditAnywhere, Category = "Grid | Materials")
// 	TSoftObjectPtr<UMaterialInterface> DefaultDecalMaterial;
// 
// 	UPROPERTY(Config, EditAnywhere, Category = "Grid | Materials")
// 	TSoftObjectPtr<UMaterialInterface> BasePlayerCursoreDecalMaterial;
// 
// 	UPROPERTY(Config, EditAnywhere, Category = "Grid | Materials")
// 	TSoftObjectPtr<UMaterialInterface> DebugDecalMaterial;

	static UPASettings* Get() { return CastChecked<UPASettings>(UPASettings::StaticClass()->GetDefaultObject()); }
};
