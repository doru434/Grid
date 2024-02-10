﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/DecalComponent.h"
#include "PADecalComponent.generated.h"

class UGridComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KD_API UPADecalComponent : public UDecalComponent
{
	GENERATED_BODY()

public:
	UPADecalComponent();

	// ActorComponent Interface
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay() override;
	// ~ActorComponent Interface
};
