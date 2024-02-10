// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerCameraMovementInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerCameraMovementInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class KD_API IPlayerCameraMovementInterface
{
	GENERATED_BODY()

public:
	virtual void MoveForward(float AxisValue) = 0;
	
	virtual void MoveRight(float AxisValue) = 0;

	virtual void Rotate(float AxisValue) = 0;

	virtual void Zoom(float AxisValue) = 0;

	virtual void ResetRotation() = 0;

	virtual void MouseCameraMovementActivation() = 0;

	virtual void MouseCameraMovementDeactivation() = 0;
};
