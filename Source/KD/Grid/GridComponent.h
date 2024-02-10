// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridTypes.h"
#include "Misc/Optional.h"
#include "Components/ActorComponent.h"
#include "KD/Interaction/InteractionInterface.h"
#include "GridComponent.generated.h"

class UBaseGridLayout;
class UGridDecalComponent;
class UBaseInteractionComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KD_API UGridComponent : public UActorComponent, public IInteractionInterface
{
	GENERATED_BODY()

public:	
	UGridComponent();

	// ActorComponent
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// ~ActorComponent
	
	// IInteractionInterface
	virtual void OnInteractStart_Implementation(UBaseInteractionComponent* BaseInteractionComponent, const FHitResult& HitResult) override;
	virtual void OnInteractFinished_Implementation(UBaseInteractionComponent* BaseInteractionComponent, const FHitResult& HitResult) override;
	virtual void OnMouseHoverStart_Implementation(UBaseInteractionComponent* BaseInteractionComponent, const FHitResult& HitResult) override;
	virtual void OnMouseHoverFinished_Implementation(UBaseInteractionComponent* BaseInteractionComponent, const FHitResult& HitResult) override;
	// ~IInteractionInterface

	TOptional<FTileData> GetTileDataAtLocation(const FVector& Location) const;

	float GetGridTileSize() const;
	const FGridData& GetGridData() const;

protected:
	UPROPERTY()
	TArray<TObjectPtr<UGridDecalComponent>> CellDecalComponents;

	UPROPERTY(EditInstanceOnly, Instanced)
	TObjectPtr<UBaseGridLayout> GridType;
	
	UFUNCTION()
	bool GenerateGrid();
	
	UFUNCTION()
	void RegenerateGrid();

	UPROPERTY(EditAnywhere)
	FGridData GridData;

private:
	bool WasGenerated() const;
	void AlignGridToSurface();

	bool bGenerated;
};
