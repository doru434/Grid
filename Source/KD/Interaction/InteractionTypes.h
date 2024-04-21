#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "Misc/Optional.h"
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
		, InteractionInterfaceActor(nullptr)
		, bIsSubcomponent(false)
	{
	}

	FInteractionHitData(const FHitResult& Hit)
	{
		HitResult = Hit;
		InteractionInterfaceActor = Hit.GetActor()->Implements<UInteractionInterface>() ? Hit.GetActor() : nullptr;
		ActorComponent = Hit.GetActor()->FindComponentByInterface(UInteractionInterface::StaticClass());

		UObject* ObjectPtr = ActorComponent;
		if (!ObjectPtr && InteractionInterfaceActor)
		{
			ObjectPtr = InteractionInterfaceActor;
		}

		if (ObjectPtr)
		{
			Payload = IInteractionInterface::Execute_GetPayload(ObjectPtr, HitResult);
			bIsSubcomponent = IInteractionInterface::Execute_IsSubcomponent(ObjectPtr, HitResult);
			if(bIsSubcomponent)
			{
				ID = IInteractionInterface::Execute_GetSubcomponentID(ObjectPtr,HitResult);
			}
		}
	}

	UPROPERTY(EditAnywhere)
	FHitResult HitResult;

	UPROPERTY(EditAnywhere)
	AActor* InteractionInterfaceActor;

	UPROPERTY(EditAnywhere)
	UActorComponent* ActorComponent;

	UPROPERTY(EditAnywhere)
	bool bIsSubcomponent;

	UPROPERTY()
	uint32 ID;
	
	UPROPERTY()
	UPayloadInteractionData* Payload;

	FORCEINLINE void SetHitResult(FHitResult& InHitResult) const { InHitResult = HitResult; }

	void Reset();
	bool IsValid() const;
	bool IsEqual(const FInteractionHitData& Other) const
	{
		return	InteractionInterfaceActor == Other.InteractionInterfaceActor
				&& ActorComponent == Other.ActorComponent
				&& Payload == Other.Payload
				&& bIsSubcomponent ? ID == Other.ID : true;
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