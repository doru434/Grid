// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionInterface.h"
#include "InteractionTypes.h"
#include "BaseInteractionComponent.generated.h"

class ABaseTopDownPlayerPawn;
class UInputComponent;

	
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KD_API UBaseInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBaseInteractionComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

private:
	UPROPERTY()
	FInteractionData InteractionData;

	UPROPERTY()
	FHoverData HoverData;

	TObjectPtr<APlayerController> PlayerController;
	TObjectPtr<ABaseTopDownPlayerPawn> BaseTopDownPlayerPawn;
	
	void OnInteractionStart();
	void OnInteractionEnd();
	void PupulateInteractionDataWithHoverData(FInteractionHitData& InteractionComponentHitData);

	void CollectInteractionData(EInteractionState InteractionState);
	void ClearInteractionData();

	bool GetHitUnderMouse(FHitResult& HitResult) const;

	void ResolveHovering(const FHitResult& Hit);
	void PupulateHoverData(const FHitResult& Hit);
	void UnhoverPrevious();

	void TryPopulatePlayerController();
};
