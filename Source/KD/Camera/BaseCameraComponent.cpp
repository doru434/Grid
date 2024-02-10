// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCameraComponent.h"
#include <Camera/CameraComponent.h>
#include <Components/SceneComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Kismet/GameplayStatics.h>
#include "../Core/BasePlayerController.h"

// Sets default values for this component's properties
UBaseCameraComponent::UBaseCameraComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->TargetArmLength = 400.f;
	SpringArmComponent->SetRelativeRotation(FRotator(-75.f, 0.f, 0.f));
	SpringArmComponent->SetupAttachment(this);
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->bEnableCameraRotationLag = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void UBaseCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	if (SpringArmComponent)
	{
		SpringArmComponent->TargetArmLength = CameraParamsData.MinCameraHeight + ((CameraParamsData.MaxCameraHeight - CameraParamsData.MinCameraHeight) / 2);
		SpringArmComponent->SetRelativeRotation(
			FMath::Lerp(CameraParamsData.MinCameraRotation,
				CameraParamsData.MaxCameraRotation,
				(SpringArmComponent->TargetArmLength - CameraParamsData.MinCameraHeight) / (CameraParamsData.MaxCameraHeight - CameraParamsData.MinCameraHeight)
			));
	}
}
 
void UBaseCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// -- Camera movement and rotattion 
	if (!bCameraMovementMouseButtonPressed)
	{
		MoveCameraByMouse();
	}

	if (bCameraMovementMouseButtonPressed)
	{
		FVector2D NewMousePosition;

		const ABasePlayerController* Controller = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		check(Controller);

		Controller->GetMousePosition(NewMousePosition.X, NewMousePosition.Y);
		DeltaMousePosition.X = BaseMousePosition.X - NewMousePosition.X;
		DeltaMousePosition.Y = BaseMousePosition.Y - NewMousePosition.Y;

		//ZoomCameraByMouse();
		RotateCameraByMouse();

		BaseMousePosition = NewMousePosition;
	}
}

void UBaseCameraComponent::MouseCameraMovementActivation()
{
	const ABasePlayerController* Controller = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	check(Controller);

	bCameraMovementMouseButtonPressed = true;
	Controller->GetMousePosition(BaseMousePosition.X, BaseMousePosition.Y);
}

void UBaseCameraComponent::MouseCameraMovementDeactivation()
{
	bCameraMovementMouseButtonPressed = false;
	BaseMousePosition.X = 0;
	BaseMousePosition.Y = 0;
}

void UBaseCameraComponent::Rotate(float AxisValue)
{
	const FRotator PreviousRotation = this->GetRelativeRotation();
	const FRotator NewRotation(PreviousRotation.Pitch, PreviousRotation.Yaw + (CameraParamsData.RotationSpeed * AxisValue), PreviousRotation.Roll);
	this->SetRelativeRotation(NewRotation);
}

void UBaseCameraComponent::Zoom(const float AxisValue) const
{
	if (AxisValue > 0)
	{
		if (SpringArmComponent->TargetArmLength + (AxisValue * CameraParamsData.CameraZoomingSpeed) <= CameraParamsData.MaxCameraHeight)
		{
			SpringArmComponent->TargetArmLength = SpringArmComponent->TargetArmLength + (AxisValue * CameraParamsData.CameraZoomingSpeed);
		}
	}
	else
	{
		if (SpringArmComponent->TargetArmLength - (AxisValue * CameraParamsData.CameraZoomingSpeed) >= CameraParamsData.MinCameraHeight)
		{
			SpringArmComponent->TargetArmLength = SpringArmComponent->TargetArmLength + (AxisValue * CameraParamsData.CameraZoomingSpeed);
		}
	}

	if (CameraParamsData.AllowRotation)
	{
		const FRotator NewRotation = FMath::Lerp(CameraParamsData.MinCameraRotation,CameraParamsData.MaxCameraRotation,(SpringArmComponent->TargetArmLength - CameraParamsData.MinCameraHeight) / (CameraParamsData.MaxCameraHeight - CameraParamsData.MinCameraHeight));
		SpringArmComponent->SetRelativeRotation(NewRotation);
		//this->SetRelativeRotation(FRotator(this->GetRelativeRotation().Pitch,0.f,this->GetRelativeRotation().Roll));
	}
}

void UBaseCameraComponent::ResetRotation()
{
	if (!bCameraMovementMouseButtonPressed)
	{
		SpringArmComponent->SetRelativeRotation(FRotator(-52.5f, 0.f, 0.f));
		this->SetRelativeRotation(FRotator(0.f,0.f,0.f));
	}
}

FCameraParamsData& UBaseCameraComponent::GetCameraParamsData()
{
	return CameraParamsData;
}

void UBaseCameraComponent::MoveCameraByMouse() const
{
	float MouseLocationX;
	float MouseLocationY;
	const ABasePlayerController* Controller = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	check(Controller);
	Controller->GetMousePosition(MouseLocationX, MouseLocationY);

	const FVector2D GameViewportSize = Controller->GetGameViewportSize();
	const FVector Forward = GetForwardVector();
	const FVector Right = GetRightVector();
	APawn* PawnOwner = Cast<APawn>(GetOwner());
	check(PawnOwner);

	if(CameraParamsData.bScreenMarginMovement)
	{
		if (MouseLocationX < CameraParamsData.ScreenMargin)
		{
			PawnOwner->AddActorWorldOffset(Right * -1 * CameraParamsData.CameraSpeed);
		}
		if (MouseLocationX > GameViewportSize.X - CameraParamsData.ScreenMargin)
		{
			PawnOwner->AddActorWorldOffset(Right * 1 * CameraParamsData.CameraSpeed);
		}

		if (MouseLocationY > GameViewportSize.Y - CameraParamsData.ScreenMargin)
		{
			PawnOwner->AddActorWorldOffset(Forward * -1 * CameraParamsData.CameraSpeed);
		}

		if (MouseLocationY < CameraParamsData.ScreenMargin)
		{
			PawnOwner->AddActorWorldOffset(Forward * 1 * CameraParamsData.CameraSpeed);
		}
	}
}

void UBaseCameraComponent::ZoomCameraByMouse() const
{
	Zoom(DeltaMousePosition.Y * (-0.05));
}

void UBaseCameraComponent::RotateCameraByMouse()
{
	Rotate(DeltaMousePosition.X * (CameraParamsData.RotationSpeed));
}

