// Fill out your copyright notice in the Description page of Project Settings.


#include "KD/Grid/GridComponent.h"
#include "KD/Core/KDTypes.h"
#include "DrawDebugHelpers.h"
#include "GridWorldSubsystem.h"
#include "GridLayouts/BaseGridLayout.h"
#include "KD/ProceduralMesh/GridProceduralMeshComponent.h"
#include "GridDecalComponent.h"
#include "KD/Interaction/BaseInteractionComponent.h"
#include "KD/PLayer/BaseTopDownPlayerPawn.h"
#include "GridSettings.h"

// Sets default values for this component's properties
UGridComponent::UGridComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	bWantsInitializeComponent = true;
}

void UGridComponent::BeginPlay()
{
	Super::BeginPlay();

	if(UGridWorldSubsystem* GridWorldSubsystem = UGridWorldSubsystem::Get(this))
	{
		GridWorldSubsystem->RegisterGridComponent(this);

		GenerateGrid(); 
		GridData.GridSizeChangedDelegate.BindDynamic(this, &UGridComponent::RegenerateGrid);
	}
}

void UGridComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UGridWorldSubsystem* GridWorldSubsystem = UGridWorldSubsystem::Get(this);
	if(GridWorldSubsystem && IsValid(this))
	{
		GridWorldSubsystem->UnregisterGridComponent(this);
	}
	
	Super::EndPlay(EndPlayReason);
}

TOptional<FTileData> UGridComponent::GetTileDataAtLocation(const FVector& Location) const
{
	TOptional<FTileData> TileData;
	if(WasGenerated())
	{
		TileData = GridType->GetTileAtLocation(GridData, Location);
	}

	return TileData;
}

float UGridComponent::GetGridTileSize() const
{
	return GridData.TileSize;
}

const FGridData& UGridComponent::GetGridData() const
{
	return GridData;
}

bool UGridComponent::GenerateGrid()
{
	ensure(GridType);

	if(GridData.bFitToParent)
	{
		FVector Origin;
		FVector BoxExtent;
		GetOwner()->GetActorBounds(true, Origin, BoxExtent, false);
		
		GridData.HalfParentSize = BoxExtent;
		GridData.ParentRoot = Origin;
	}
	
	bGenerated = GridType->GenerateGrid(GridData);
	AlignGridToSurface();

#if KD_GRAPHIC_LOG
	{
		for(int i=0; i < GridData.Grid.Num(); i++)
		{
			for(int j=0; j < GridData.Grid[i].Tile.Num(); j++)
			{
				DrawDebugPoint(this->GetWorld(), GridData.Grid[i].Tile[j].TilePosition, 5.f, FColor::Emerald,true, 50.f);						
			}
		}
	}
#endif
	
	return bGenerated;
}

void UGridComponent::RegenerateGrid()
{
	GenerateGrid();
}

bool UGridComponent::WasGenerated() const
{
	return bGenerated;
}

void UGridComponent::AlignGridToSurface()
{
	for(int i=0; i < GridData.Grid.Num(); i++)
	{
		for(int j=0; j < GridData.Grid[i].Tile.Num(); j++)
		{
			FHitResult Hit;
			FVector Start = GridData.Grid[i].Tile[j].TilePosition;
			Start.Z = Start.Z + 2000.f;

			FVector End  = GridData.Grid[i].Tile[j].TilePosition;
			End.Z = End.Z - 2000.f;

			FCollisionQueryParams Params;
			FCollisionResponseParams ResponseParam;
			GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_WorldStatic, Params, ResponseParam);
			
			GridData.Grid[i].Tile[j].TilePosition.Z = Hit.Location.Z + 10.0;
		}
	}
}

void UGridComponent::OnInteractionBegining_Implementation(const UBaseInteractionComponent* BaseInteractionComponent, const FHitResult& HitResult)
{

}

void UGridComponent::OnInteractionEnd_Implementation(const UBaseInteractionComponent* BaseInteractionComponent, const FHitResult& HitResult)
{

}

void UGridComponent::OnMouseHoverBegining_Implementation(const UBaseInteractionComponent* BaseInteractionComponent, const FHitResult& HitResult)
{
	ABaseTopDownPlayerPawn* BaseTopDownPlayerPawn = Cast<ABaseTopDownPlayerPawn>(BaseInteractionComponent->GetOwner());
	if(BaseTopDownPlayerPawn)
	{
		TOptional<FTileData> TileData = GetTileDataAtLocation(HitResult.Location);
		if (TileData.IsSet())
		{
#if KD_LOG
			if (GEngine)
			{
				const FString OnScreenMessage = FString::Printf(TEXT("Tile location: %f %f"), TileData.GetValue().TilePosition.X, TileData.GetValue().TilePosition.Y);
				GEngine->AddOnScreenDebugMessage(3, 2.f, FColor::Emerald, OnScreenMessage);
			}
#endif
			BaseTopDownPlayerPawn->OnTooltipChange(true, TileData.GetValue(), GetGridTileSize());
		}
	}
}

void UGridComponent::OnMouseHoverEnd_Implementation(const UBaseInteractionComponent* BaseInteractionComponent, const FHitResult& HitResult)
{
	ABaseTopDownPlayerPawn* BaseTopDownPlayerPawn = Cast<ABaseTopDownPlayerPawn>(BaseInteractionComponent->GetOwner());
	if (BaseTopDownPlayerPawn)
	{
		BaseTopDownPlayerPawn->UpdatePlayerCursor(false);
	}
}

UPayloadInteractionData* UGridComponent::GetPayload_Implementation(const FHitResult& HitResult)
{
	UPayloadInteractionData* Payload = nullptr;

	TOptional<FTileData> TileData = GetTileDataAtLocation(HitResult.Location);
	if (TileData.IsSet())
	{

	}

	return Payload;
}

bool UGridComponent::IsSubcomponent_Implementation(const FHitResult& HitResult)
{
	return true;
}

int32 UGridComponent::GetSubcomponentID_Implementation(const FHitResult& HitResult)
{
	uint32 ID = 0;
	const TOptional<FTileData> TileData = GetTileDataAtLocation(HitResult.Location);
	if (TileData.IsSet())
	{
		const FTileData& TileDataRef = TileData.GetValue();
		ID = TileDataRef.ID;
#if KD_LOG
		if (GEngine)
		{
			const FString OnScreenMessage = FString::Printf(TEXT("SubcomponentID %d at position Tile location: %f %f"), ID, TileDataRef.TilePosition.X, TileDataRef.TilePosition.Y);
			GEngine->AddOnScreenDebugMessage(4, 2.f, FColor::Emerald, OnScreenMessage);
		}
#endif
	}

	return ID;
}

