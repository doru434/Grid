// Fill out your copyright notice in the Description page of Project Settings.

#include "PADecalActor.h"
#include "PADecalComponent.h"

// Sets default values
APADecalActor::APADecalActor()
{
	PrimaryActorTick.bCanEverTick = true;

	PADecalComponent = CreateDefaultSubobject<UPADecalComponent>(TEXT("PADecalComponent"));
	PADecalComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APADecalActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APADecalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APADecalActor::BeginDestroy()
{
// 	if (PADecalComponent)
// 	{
// 		PADecalComponent->DestroyComponent();
// 	}
// 	UE_LOG(LogTemp, Warning, TEXT("APADecalActor::BeginDestroy()"));

	Super::BeginDestroy();
}


