// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KD/Interaction/InteractionInterface.h"
#include "KDBaseCharacter.generated.h"

class UDecalComponent;
class UBaseInteractionComponent;

UCLASS()
class KD_API AKDBaseCharacter : public ACharacter, public IInteractionInterface
{
	GENERATED_UCLASS_BODY()

public:
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;

	// IInteractionInterface
	virtual void OnInteractionBegining_Implementation(const UBaseInteractionComponent* BaseInteractionComponent, const FHitResult& HitResult) override;
	virtual void OnInteractionEnd_Implementation(const UBaseInteractionComponent* BaseInteractionComponent, const FHitResult& HitResult) override;
	virtual void OnMouseHoverBegining_Implementation(const UBaseInteractionComponent* BaseInteractionComponent, const FHitResult& HitResult) override;
	virtual void OnMouseHoverEnd_Implementation(const UBaseInteractionComponent* BaseInteractionComponent, const FHitResult& HitResult) override;
	// ~IInteractionInterface

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class UDecalComponent* DecalComp;
};
