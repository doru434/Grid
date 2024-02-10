// Fill out your copyright notice in the Description page of Project Settings.


#include "KD/PastedArea/PAWorldSubsystem.h"


UPAWorldSubsystem* UPAWorldSubsystem::Get(const UObject* WorldContextObject)
{
	const UWorld* WorldRaw = WorldContextObject->GetWorld();
	return WorldRaw->GetSubsystem<UPAWorldSubsystem>();
}

void UPAWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UPAWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
}