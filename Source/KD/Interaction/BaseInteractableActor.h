// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "BaseInteractableActor.generated.h"

class UBaseInteractionComponent;

//UDELEGATE(BlueprintImplementableEvent)
//DECLARE_DYNAMIC_DELEGATE_RetVal(FVector, FPositionDelegateSignature);



UCLASS()
class KD_API ABaseInteractableActor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseInteractableActor();


	FInstigatedAnyDamageSignature InstigatedAnyDamageSignature;

	// IInteractionInterface
	virtual void OnInteractionBegining_Implementation(const UBaseInteractionComponent* BaseInteractionComponent, const FHitResult& HitResult) override;
	virtual void OnInteractionEnd_Implementation(const UBaseInteractionComponent* BaseInteractionComponent, const FHitResult& HitResult) override;

	virtual void OnMouseHoverBegining_Implementation(const UBaseInteractionComponent* BaseInteractionComponent, const FHitResult& HitResult) override;
	virtual void OnMouseHoverEnd_Implementation(const UBaseInteractionComponent* BaseInteractionComponent, const FHitResult& HitResult) override;
	// ~IInteractionInterface 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
