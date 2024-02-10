#pragma once

#include "CoreMinimal.h"
#include "PADecalActor.h"
#include "PATypes.generated.h"

UENUM(BlueprintType)
enum class EPastedAreaType : uint8
{
	Line,
	Decal,
	Circle
};

USTRUCT(BlueprintType)
struct FPastedAreaSpawnInfo
{
	GENERATED_BODY()

	FPastedAreaSpawnInfo()
		: Transform(FTransform::Identity)
		, DecalMaterial(nullptr) // KDTODO : make default material
		, DecalLifeSpan(0.0f)
	{
	}

	FPastedAreaSpawnInfo(FTransform InTransform, UMaterialInterface* InDecalMaterial, float InDecalLifeSpan)
	{
		Transform = InTransform;
		DecalMaterial = InDecalMaterial;
		DecalLifeSpan = InDecalLifeSpan;
	}

	UPROPERTY(EditAnywhere)
	FTransform Transform;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* DecalMaterial;

	UPROPERTY(EditAnywhere)
	float DecalLifeSpan;
};

USTRUCT()
struct FPAObjectData
{
	GENERATED_BODY()

	FPAObjectData()
		: ID(0)
		, DecalActor(nullptr)
		, Orderer(nullptr)
	{
	}

	~FPAObjectData()
	{
		UE_LOG(LogTemp, Warning, TEXT("FPAObjectData Destroyed"));
	}

	FPAObjectData(TObjectPtr<APADecalActor> InDecalActor, TWeakObjectPtr<AActor> InOrderer)
	{
		ID = GetUniqueID();
		DecalActor = InDecalActor;
		Orderer = InOrderer;
	}

public:
	FORCEINLINE TObjectPtr<APADecalActor> GetDecalActor() const
	{
		return DecalActor;
	}

	FORCEINLINE TWeakObjectPtr<AActor> GetOrderer() const
	{
		return Orderer;
	}

	bool operator==(const FPAObjectData& Other) const
	{
		return Other.GetID() == GetID();
	}

	uint32 GetID() const
	{
		return ID;
	}

	friend uint32 GetTypeHash(const FPAObjectData& Other)
	{
		return GetTypeHash(Other.GetID());
	}

private:
	uint32 ID;

	UPROPERTY()
	TObjectPtr<APADecalActor> DecalActor;

	UPROPERTY()
	TWeakObjectPtr<AActor> Orderer;

	uint32 GetUniqueID() const
	{
		static uint32 CurrentID = 0;
		return ++CurrentID;
	}
};
