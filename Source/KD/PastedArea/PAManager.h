// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "PATypes.h"
#include "PAManager.generated.h"

class APADecalActor;

UCLASS()
class KD_API APAManager : public AInfo
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APAManager();

	// AActor interface
	virtual void Tick(float DeltaTime) override;
	// End AActor interface

	UFUNCTION(BlueprintCallable, meta = (Category = "DecalManager"))
	int32 SpawnDecalActor(const FPastedAreaSpawnInfo& PastedAreaSpawnInfo, AActor* Orderer);

	UFUNCTION(BlueprintCallable, meta = (Category = "DecalManager"))
	void DestroyDecalActor(int32 ID);

	UFUNCTION(BlueprintCallable, meta = (Category = "DecalManager"))
	void DestroyDecalActorsByOrderer(AActor* Orderer);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TMap<int32, FPAObjectData> PAObjects;
};
