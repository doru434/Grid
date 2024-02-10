// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PAWorldSubsystem.generated.h"


UCLASS()
class KD_API UPAWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	static UPAWorldSubsystem* Get(const UObject* WorldContextObject);
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
};
