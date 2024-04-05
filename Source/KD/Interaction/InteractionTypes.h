#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "Engine/DataAsset.h"
#include "InteractionTypes.generated.h"

UENUM(BlueprintType)
enum class EInteractionComponentState : uint8
{
	Basic,
	Selecting,
	Building
};

UENUM(BlueprintType)
enum class EInteractionState : uint8
{
	Initial,
	Final
};

UCLASS(Abstract)
class UPayloadInteractionData : public UObject
{
	GENERATED_BODY()

public:
	bool operator==(const UPayloadInteractionData& Other)
	{
		return IsEqual(&Other);
	}

protected:
	virtual bool IsEqual(const UPayloadInteractionData* Other) const { return true; }
};

USTRUCT(BlueprintType)
struct FInteractionHitData
{
	GENERATED_BODY()

	FInteractionHitData()
		: HitResult(FHitResult())
		, Actor(nullptr)
	{
	}

	FInteractionHitData(const FHitResult& Hit)
	{
		HitResult = Hit;
		Actor = Hit.GetActor();
		ActorComponent = Actor->FindComponentByInterface(UInteractionInterface::StaticClass());

		UObject* ObjectPtr = ActorComponent;
		if (!ObjectPtr)
		{
			ObjectPtr = Actor->Implements<UInteractionInterface>() ? Actor : nullptr;
		}

		if (ObjectPtr)
		{
			Payload = IInteractionInterface::Execute_GetPayload(ObjectPtr, HitResult);
		}
	}

	UPROPERTY(EditAnywhere)
	FHitResult HitResult;

	UPROPERTY(EditAnywhere)
	AActor* Actor;

	UPROPERTY(EditAnywhere)
	UActorComponent* ActorComponent;

	UPROPERTY()
	UPayloadInteractionData* Payload;

	FORCEINLINE void SetHitResult(FHitResult& InHitResult) const { InHitResult = HitResult; }

	void Reset();
	bool IsValid() const;
	bool IsEqual(const FInteractionHitData& Other) const
	{
		return	Actor == Other.Actor
				&& ActorComponent == Other.ActorComponent
				&& Payload == Other.Payload;
	}
};
	

USTRUCT(BlueprintType)
struct FInteractionData
{
	GENERATED_BODY()

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
	GENERATED_BODY()

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

	bool IsValid() const;
	void ClearData();

	void OnMouseHoverBegining(const UBaseInteractionComponent* BaseInteractionComponent);
	void OnMouseHoverEnd(const UBaseInteractionComponent* BaseInteractionComponent);

	bool IsEqual(const FHoverData& Other) const
	{
		return  HoverInteractionHitData.IsEqual(Other.HoverInteractionHitData);
	}
};