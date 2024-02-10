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
	virtual void OnInteractStart_Implementation(UBaseInteractionComponent* BaseInteractionComponent, const FHitResult& HitResult) override;
	virtual void OnInteractFinished_Implementation(UBaseInteractionComponent* BaseInteractionComponent, const FHitResult& HitResult) override;
	virtual void OnMouseHoverStart_Implementation(UBaseInteractionComponent* BaseInteractionComponent, const FHitResult& HitResult) override;
	virtual void OnMouseHoverFinished_Implementation(UBaseInteractionComponent* BaseInteractionComponent, const FHitResult& HitResult) override;
	// ~IInteractionInterface

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class UDecalComponent* DecalComp;
};
