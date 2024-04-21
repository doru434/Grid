// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionInterface.h"
#include "InteractionTypes.h"
#include "BaseInteractionComponent.generated.h"

class ABaseTopDownPlayerPawn;
class UInputComponent;
class UInputAction;
struct FInputActionValue;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KD_API UBaseInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBaseInteractionComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> MainAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> BuildModeAction;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

private:
	UPROPERTY()
	FInteractionData InteractionData;

	UPROPERTY()
	FHoverData HoverData;

	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY()
	TObjectPtr<ABaseTopDownPlayerPawn> BaseTopDownPlayerPawn;
	
	EInteractionComponentState InteractionComponentState;

	void OnMainActionPressed(const FInputActionValue& Value);
	void OnMainActionReleased(const FInputActionValue& Value);

	void OnBuildModePressed(const FInputActionValue& Value);


	void PupulateInteractionDataWithHoverData(FInteractionHitData& InteractionComponentHitData);

	void CollectInteractionData(EInteractionState InteractionState);
	void ClearInteractionData();

	bool GetHitUnderMouse(FHitResult& HitResult) const;

	void ResolveHovering(const FHitResult& Hit);

	bool HasHoverChanged(const FHoverData& InHoverData) const;
	void UnhoverPrevious();

	void TryPopulatePlayerController();
};
