// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "KD/Camera/PlayerCameraMovementInterface.h"
#include "KD/Player/BaseTopDownPlayerPawn.h"
#include "KD/Interaction/BaseInteractionComponent.h"

ABasePlayerController::ABasePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ABasePlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ABasePlayerController::MoveRight);
	InputComponent->BindAxis("Rotate", this, &ABasePlayerController::Rotate);
	InputComponent->BindAxis("Zoom", this, &ABasePlayerController::Zoom);

	InputComponent->BindAction("MouseCameraMovementKey", IE_Pressed, this, &ABasePlayerController::MouseCameraMovementActivation);
	InputComponent->BindAction("MouseCameraMovementKey", IE_Released, this, &ABasePlayerController::MouseCameraMovementDeactivation);
	InputComponent->BindAction("ResetRotation", IE_Pressed, this, &ABasePlayerController::ResetRotation);

	InputComponent->BindAction("MainAction", IE_Pressed, this, &ABasePlayerController::MainAction);
}

FVector2D ABasePlayerController::GetGameViewportSize()
{
	FVector2D Result = FVector2D::ZeroVector;

	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(OUT Result);
	}

	return Result;
}

FVector2D ABasePlayerController::GetGameResolution()
{
	FVector2D Result = FVector2D::ZeroVector;

	Result.X = GSystemResolution.ResX;
	Result.Y = GSystemResolution.ResY;

	return Result;
}

IPlayerCameraMovementInterface* ABasePlayerController::GetPlayerCameraMovementInterface() const
{
	APawn* ControlledPawn = this->GetPawn();
	check(ControlledPawn->Implements<UPlayerCameraMovementInterface>());
	return Cast<IPlayerCameraMovementInterface>(ControlledPawn);
}

void ABasePlayerController::MoveForward(float AxisValue)
{
	if (!FMath::IsNearlyZero(AxisValue))
	{
		IPlayerCameraMovementInterface* PlayerCameraMovementInterface = GetPlayerCameraMovementInterface();
		PlayerCameraMovementInterface->MoveForward(AxisValue);
	}
}

void ABasePlayerController::MoveRight(float AxisValue)
{
	if (!FMath::IsNearlyZero(AxisValue))
	{
		IPlayerCameraMovementInterface* PlayerCameraMovementInterface = GetPlayerCameraMovementInterface();
		PlayerCameraMovementInterface->MoveRight(AxisValue);
	}
}

void ABasePlayerController::Rotate(float AxisValue)
{
	if (!FMath::IsNearlyZero(AxisValue))
	{
		IPlayerCameraMovementInterface* PlayerCameraMovementInterface = GetPlayerCameraMovementInterface();
		PlayerCameraMovementInterface->Rotate(AxisValue);
	}
}

void ABasePlayerController::Zoom(float AxisValue)
{
	if (!FMath::IsNearlyZero(AxisValue))
	{
		IPlayerCameraMovementInterface* PlayerCameraMovementInterface = GetPlayerCameraMovementInterface();
		PlayerCameraMovementInterface->Zoom(AxisValue);
	}
}

void ABasePlayerController::MouseCameraMovementActivation()
{
	IPlayerCameraMovementInterface* PlayerCameraMovementInterface = GetPlayerCameraMovementInterface();
	PlayerCameraMovementInterface->MouseCameraMovementActivation();
}

void ABasePlayerController::MouseCameraMovementDeactivation()
{
	IPlayerCameraMovementInterface* PlayerCameraMovementInterface = GetPlayerCameraMovementInterface();
	PlayerCameraMovementInterface->MouseCameraMovementDeactivation();
}

void ABasePlayerController::ResetRotation()
{	
	IPlayerCameraMovementInterface* PlayerCameraMovementInterface = GetPlayerCameraMovementInterface();
	PlayerCameraMovementInterface->ResetRotation();
}


void ABasePlayerController::MainAction()
{

}
