// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

class IPlayerCameraMovementInterface;

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

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:

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
	virtual void MainAction();
};
