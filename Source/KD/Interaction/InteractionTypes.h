#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "InteractionTypes.generated.h"

UENUM(BlueprintType)
enum class EInteractionState : uint8
{
	Initial,
	Final
};

USTRUCT(BlueprintType)
struct FInteractionHitData
{
	GENERATED_USTRUCT_BODY()

	FInteractionHitData()
		: HitResult(FHitResult())
		, Actor(nullptr)
	{
	}

	FInteractionHitData(const FHitResult& Hit)
	{
		HitResult = Hit;
		Actor = Hit.GetActor();
		ActorComponents = Actor->GetComponentsByInterface(UInteractionInterface::StaticClass());
	}

	UPROPERTY(EditAnywhere)
	FHitResult HitResult;

	UPROPERTY(EditAnywhere)
	AActor* Actor;

	UPROPERTY(EditAnywhere)
	TArray<UActorComponent*> ActorComponents;

	FORCEINLINE void SetHitResult(FHitResult& InHitResult) const { InHitResult = HitResult; }

	void Reset();
	bool IsValid() const;
	bool operator == (const FInteractionHitData& Other)
	{
		return  HitResult.Location == Other.HitResult.Location
				&& Actor == Other.Actor
				&& ActorComponents == Other.ActorComponents;
	}
};
	

USTRUCT(BlueprintType)
struct FInteractionData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FInteractionHitData InitialHitData;

	UPROPERTY(EditAnywhere)
	FInteractionHitData FinalHitData;

	bool IsValid() const;
	void ClearData();

	void OnInteractionStart(const UBaseInteractionComponent* InteractionComponent);
	void OnInteractionEnd(const UBaseInteractionComponent* InteractionComponent);
};

USTRUCT(BlueprintType)
struct FHoverData
{ 
	GENERATED_USTRUCT_BODY()

	FHoverData()
		: HoverInteractionHitData(FInteractionHitData())
	{
	}

	FHoverData(const FHitResult& Hit)
		: HoverInteractionHitData(FInteractionHitData(Hit))
	{
	}

	UPROPERTY(EditAnywhere)
	FInteractionHitData HoverInteractionHitData;

	FORCEINLINE void GetHitResult(FHitResult& InHitResult) { HoverInteractionHitData.SetHitResult(InHitResult); }

	bool IsValid() const;
	void ClearData();

	void OnMouseHoverBegining(const UBaseInteractionComponent* BaseInteractionComponent);
	void OnMouseHoverEnd(const UBaseInteractionComponent* BaseInteractionComponent);
};