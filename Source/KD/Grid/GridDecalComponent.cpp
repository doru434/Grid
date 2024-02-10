// Fill out your copyright notice in the Description page of Project Settings.


#include "GridDecalComponent.h"
#include "GridComponent.h"
#include "KD/Grid/GridSettings.h"

UGridDecalComponent::UGridDecalComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	const UGridSettings* GridSettingsRaw = UGridSettings::Get();
	UMaterialInterface* MaterialInterface = GridSettingsRaw->DefaultDecalMaterial.Get();
	
	MaterialInterface ? DecalMaterial = MaterialInterface : DecalMaterial = GridSettingsRaw->DefaultDecalMaterial.LoadSynchronous();

	DecalSize = FVector(GridSettingsRaw->BaseDecalZSize, DecalSize.Y, DecalSize.Z);
	SetWorldRotation(GridSettingsRaw->TopDownDecal);
}

void UGridDecalComponent::UpdateDecalSize(const float Size)
{
	const FVector& Scale = GetComponentScale();
	DecalSize = FVector(DecalSize.X, Size * 0.5, Size * 0.5);
	DecalSize = FVector(DecalSize.X / Scale.X, DecalSize.Y / Scale.Y, DecalSize.Z / Scale.Z);
}

void UGridDecalComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UGridDecalComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

