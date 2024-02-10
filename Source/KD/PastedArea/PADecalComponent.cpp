// Fill out your copyright notice in the Description page of Project Settings.


#include "PADecalComponent.h"

UPADecalComponent::UPADecalComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UPADecalComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPADecalComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

