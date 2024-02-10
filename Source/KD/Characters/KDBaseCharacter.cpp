// Fill out your copyright notice in the Description page of Project Settings.


#include "KDBaseCharacter.h"
#include "Components/DecalComponent.h"
#include "KD/KDSettings.h"
#include "KD/Interaction/BaseInteractionComponent.h"

AKDBaseCharacter::AKDBaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	DecalComp = ObjectInitializer.CreateDefaultSubobject<UDecalComponent>(this, TEXT("DecalComp"));
	DecalComp->SetupAttachment(RootComponent);
	DecalComp->SetRelativeRotation(FRotator(-90.0, 0.0, 0));
	DecalComp->SetRelativeLocation(FVector(0.0, 0.0, -100.0));
	DecalComp->SetVisibility(false);

	const UKDSettings* KDSettings = UKDSettings::Get();
	check(KDSettings);

	DecalComp->DecalSize = KDSettings->DefaultCharacterSelectionDecalSize;

	if (KDSettings->DefaultCharacterSelectionDecalMaterial.IsValid())
	{
		DecalComp->SetDecalMaterial(KDSettings->DefaultCharacterSelectionDecalMaterial.Get());
	}
}

void AKDBaseCharacter::BeginPlay()
{
	Super::BeginPlay();	
}

void AKDBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AKDBaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AKDBaseCharacter::OnMouseHoverFinished_Implementation(UBaseInteractionComponent* BaseInteractionComponent, const FHitResult& HitResult)
{
	
}

void AKDBaseCharacter::OnMouseHoverStart_Implementation(UBaseInteractionComponent* BaseInteractionComponent, const FHitResult& HitResult)
{
	
}

void AKDBaseCharacter::OnInteractFinished_Implementation(UBaseInteractionComponent* BaseInteractionComponent, const FHitResult& HitResult)
{
	DecalComp->SetVisibility(false);
}

void AKDBaseCharacter::OnInteractStart_Implementation(UBaseInteractionComponent* BaseInteractionComponent, const FHitResult& HitResult)
{
	DecalComp->SetVisibility(true);
}

