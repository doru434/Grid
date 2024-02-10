// Fill out your copyright notice in the Description page of Project Settings.

#include "PAManager.h"
#include "PADecalActor.h"

APAManager::APAManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APAManager::BeginPlay()
{
	Super::BeginPlay();
}

void APAManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (auto& [key, value] : PAObjects)
	{
		if (value.GetDecalActor())
		{	
			FStringView StringView = value.GetDecalActor()->GetName();
			//UE_LOG(LogTemp, Warning, TEXT("DecalActor Name: "), StringView);
		}
	}
}

int32 APAManager::SpawnDecalActor(const FPastedAreaSpawnInfo& PastedAreaSpawnInfo, AActor* Orderer)
{
	ensure(Orderer);

	int32 ID = 0;

	APADecalActor* DecalActor = GetWorld()->SpawnActor<APADecalActor>(APADecalActor::StaticClass(), PastedAreaSpawnInfo.Transform);
	if (DecalActor && Orderer)
	{
		FPAObjectData PAObject(DecalActor, MakeWeakObjectPtr(Orderer));
		ID = PAObject.GetID();

		PAObjects.Add(ID, std::move(PAObject));
	}

	return ID;
}

void APAManager::DestroyDecalActor(int32 ID)
{
	FPAObjectData* PAObject = PAObjects.Find(ID);
	if (PAObject)
	{
		PAObject->GetDecalActor()->Destroy();
		UE_LOG(LogTemp, Warning, TEXT("DestroyDecalActor: DecalActor Destroyed"));
	}

	PAObjects.Remove(ID);
}

void APAManager::DestroyDecalActorsByOrderer(AActor* Orderer)
{
	ensure(Orderer);

	TArray<uint32> Keys;
	Keys.Reserve(PAObjects.Num());

	for (auto& [ID, PAObjectData] : PAObjects)
	{
		if (PAObjectData.GetOrderer() == Orderer)
		{
			Keys.Add(ID);
		}
	}

	for (const uint32 Key : Keys)
	{
		DestroyDecalActor(Key);
	}
}

