// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridComponent.h"
#include "GridTypes.h"
#include "GridLayouts/BaseGridLayout.h"
#include "Subsystems/WorldSubsystem.h"
#include "GridWorldSubsystem.generated.h"


UCLASS()
class KD_API UGridWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	static UGridWorldSubsystem* Get(const UObject* WorldContextObject);
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	UFUNCTION(BlueprintCallable)
	void RegisterGridComponent(UGridComponent* GridComponent);

	UFUNCTION(BlueprintCallable)
	void UnregisterGridComponent(UGridComponent* GridComponent);
	
private:
	UPROPERTY()
	TSet<TWeakObjectPtr<UGridComponent>> GridComponents;
};
