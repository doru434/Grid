// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTopDownPlayerPawn.h"
#include "Components/SceneComponent.h"
#include "KD/Interaction/BaseInteractionComponent.h"
#include "KD/Camera/BaseCameraComponent.h"
#include "KD/Grid/GridDecalComponent.h"
#include "KD/Grid/GridSettings.h"


ABaseTopDownPlayerPawn::ABaseTopDownPlayerPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	CameraMovementSpeed(10.f)
{
	InteractionComponent = ObjectInitializer.CreateDefaultSubobject<UBaseInteractionComponent>(this, TEXT("InteractionComponent"));

	CameraComponent = ObjectInitializer.CreateDefaultSubobject<UBaseCameraComponent>(this, TEXT("Camera"));
	CameraComponent->SetupAttachment(RootComponent);

	CursorGridDecalComponent = ObjectInitializer.CreateDefaultSubobject<UGridDecalComponent>(this, TEXT("GridDecalComponent"));


	const UGridSettings* GridSettingsRaw = UGridSettings::Get();
	UMaterialInterface* MaterialInterface = GridSettingsRaw->BasePlayerCursoreDecalMaterial.Get();

	MaterialInterface ? CursorGridDecalComponent->SetDecalMaterial(MaterialInterface) : CursorGridDecalComponent->SetDecalMaterial(GridSettingsRaw->DefaultDecalMaterial.LoadSynchronous());

	CursorGridDecalComponent->DecalSize = FVector(50.0,12.5,12.5);
	CursorGridDecalComponent->bDestroyOwnerAfterFade = false;
}

void ABaseTopDownPlayerPawn::UpdatePlayerCursor(const bool bShow, const FVector& NewLocation, const float Size) const
{
	if (bShow)
	{
		GetCursorGridDecalComponent()->SetVisibility(bShow);
		SetCursorGridDecalComponentLocation(NewLocation);
		SetCursorGridDecalSize(Size);
	}
	else
	{
		GetCursorGridDecalComponent()->SetVisibility(bShow);
	}
}

void ABaseTopDownPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseTopDownPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//===== Begin IPlayerCameraMovementInterface
void ABaseTopDownPlayerPawn::MoveForward(float AxisValue)
{	
	if (AxisValue)
	{
		const FVector Forward = GetActorForwardVector();
		AddActorWorldOffset(Forward * (AxisValue * CameraComponent->GetCameraParamsData().CameraSpeed));
	}
}

void ABaseTopDownPlayerPawn::MoveRight(float AxisValue)
{
	if(AxisValue)
	{
		const FVector Right = GetActorRightVector();
		AddActorWorldOffset(Right * (AxisValue * CameraComponent->GetCameraParamsData().CameraSpeed));
	}
}

void ABaseTopDownPlayerPawn::Rotate(float AxisValue)
{
	CameraComponent->Rotate(AxisValue);
}

void ABaseTopDownPlayerPawn::Zoom(float AxisValue)
{
	CameraComponent->Zoom(AxisValue);
}

void ABaseTopDownPlayerPawn::ResetRotation()
{
	CameraComponent->ResetRotation();
}

void ABaseTopDownPlayerPawn::MouseCameraMovementActivation()
{
	CameraComponent->MouseCameraMovementActivation();
}

void ABaseTopDownPlayerPawn::MouseCameraMovementDeactivation()
{
	CameraComponent->MouseCameraMovementDeactivation();
}

void ABaseTopDownPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	GetInteractionComponent()->SetupPlayerInputComponent(PlayerInputComponent);
}
//===== End IPlayerCameraMovementInterface

void ABaseTopDownPlayerPawn::SetCursorGridDecalComponentLocation(const FVector& NewLocation) const
{
	CursorGridDecalComponent->SetWorldLocation(NewLocation);
}
void ABaseTopDownPlayerPawn::SetCursorGridDecalSize(const float Size) const
{
	CursorGridDecalComponent->UpdateDecalSize(Size);
}