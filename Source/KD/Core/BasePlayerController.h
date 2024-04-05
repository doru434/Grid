// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

class IPlayerCameraMovementInterface;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class KD_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ABasePlayerController();

	static FVector2D GetGameViewportSize();
	static FVector2D GetGameResolution();

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TSoftObjectPtr<UInputMappingContext> BasicInputMapping;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> MovementAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> RotationAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> ZoomAction;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:

	void OnMove(const FInputActionValue& Value);
	void OnZoom(const FInputActionValue& Value);

	// Begin IPlayerCameraMovementInterface
	IPlayerCameraMovementInterface* GetPlayerCameraMovementInterface() const;
	virtual void MoveForward(float AxisValue);
	virtual void MoveRight(float AxisValue);
	virtual void Rotate(float AxisValue);
	virtual void Zoom(float AxisValue);
	virtual void MouseCameraMovementActivation();
	virtual void MouseCameraMovementDeactivation();
	virtual void ResetRotation();
	// End IPlayerCameraMovementInterface

	IPlayerCameraMovementInterface* GetPlayerActionInterface() const;
};
