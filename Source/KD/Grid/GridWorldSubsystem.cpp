// Fill out your copyright notice in the Description page of Project Settings.


#include "KD/Grid/GridWorldSubsystem.h"


UGridWorldSubsystem* UGridWorldSubsystem::Get(const UObject* WorldContextObject)
{
	const UWorld* WorldRaw = WorldContextObject->GetWorld();
	return WorldRaw->GetSubsystem<UGridWorldSubsystem>();
}

void UGridWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UGridWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
}

void UGridWorldSubsystem::RegisterGridComponent(UGridComponent* GridComponent)
{
	ensure(GridComponent);
	if(GridComponent && !GridComponents.Contains(GridComponent))
	{
		GridComponents.Add(MakeWeakObjectPtr(GridComponent));
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Component Already Registered"));
	}
}

void UGridWorldSubsystem::UnregisterGridComponent(UGridComponent* GridComponent)
{
	ensure(GridComponent);
	if(GridComponent && GridComponents.Contains(GridComponent))
	{
		GridComponents.Remove(GridComponent);
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Component is not in set"));
	}
}

