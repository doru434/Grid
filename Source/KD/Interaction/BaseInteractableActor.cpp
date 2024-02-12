// Fill out your copyright notice in the Description page of Project Settings.
#include "BaseInteractableActor.h"
#include "KD/Core/KDTypes.h"
#include "BaseInteractionComponent.h"


// Sets default values
ABaseInteractableActor::ABaseInteractableActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseInteractableActor::OnMouseHoverEnd_Implementation(const UBaseInteractionComponent* BaseInteractionComponent, const FHitResult& HitResult)
{
	
}

void ABaseInteractableActor::OnMouseHoverBegining_Implementation(const UBaseInteractionComponent* BaseInteractionComponent, const FHitResult& HitResult)
{
	
}

void ABaseInteractableActor::OnInteractionEnd_Implementation(const UBaseInteractionComponent* BaseInteractionComponent, const FHitResult& HitResult)
{
	
}

void ABaseInteractableActor::OnInteractionBegining_Implementation(const UBaseInteractionComponent* BaseInteractionComponent, const FHitResult& HitResult)
{
	
}

// Called when the game starts or when spawned
void ABaseInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

