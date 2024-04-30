// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTopDownPlayerPawn.h"
#include "Components/SceneComponent.h"
#include "KD/Interaction/BaseInteractionComponent.h"
#include "KD/Camera/BaseCameraComponent.h"
#include "KD/Grid/GridDecalComponent.h"
#include "KD/Grid/GridSettings.h"
#include "KD/Core/KDTypes.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "KD/Core/BaseHUD.h"


ABaseTopDownPlayerPawn::ABaseTopDownPlayerPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, CameraMovementSpeed(10.f)
	, BaseHUD(nullptr)
{
	InteractionComponent = ObjectInitializer.CreateDefaultSubobject<UBaseInteractionComponent>(this, TEXT("InteractionComponent"));

	CameraComponent = ObjectInitializer.CreateDefaultSubobject<UBaseCameraComponent>(this, TEXT("Camera"));
	CameraComponent->SetupAttachment(RootComponent);

	CursorGridDecalComponent = ObjectInitializer.CreateDefaultSubobject<UGridDecalComponent>(this, TEXT("GridDecalComponent"));


	const UGridSettings* GridSettingsRaw = UGridSettings::Get();
	UMaterialInterface* MaterialInterface = GridSettingsRaw->BasePlayerCursoreDecalMaterial.Get();

	MaterialInterface ?
		  CursorGridDecalComponent->SetDecalMaterial(MaterialInterface)
		: CursorGridDecalComponent->SetDecalMaterial(GridSettingsRaw->DefaultDecalMaterial.LoadSynchronous());

	CursorGridDecalComponent->DecalSize = FVector(50.0,12.5,12.5);
	CursorGridDecalComponent->bDestroyOwnerAfterFade = false;

	MovementComponent = ObjectInitializer.CreateDefaultSubobject<UFloatingPawnMovement>(this, TEXT("MovementCompoennt"));
	MovementComponent->UpdatedComponent = RootComponent;
	
	bReplicates = true;
}

void ABaseTopDownPlayerPawn::OnTooltipChange(const bool bShow, const FTileData& TileData, const float Size)
{
	UpdatePlayerCursor(bShow, TileData.TilePosition, Size);
	UpdateTooltipWidget(bShow, TileData);
}

void ABaseTopDownPlayerPawn::UpdatePlayerCursor(const bool bShow, const FVector& NewLocation, const float Size) const
{
	if (bShow)
	{
		SetCursorGridDecalComponentLocation(NewLocation);
		SetCursorGridDecalSize(Size);
	}

	GetCursorGridDecalComponent()->SetVisibility(bShow);
}

void ABaseTopDownPlayerPawn::UpdateTooltipWidget(const bool bShow, const FTileData& TileData)
{
	if(!BaseHUD)
	{
		CacheBaseHUD();
	}

	check(BaseHUD);
	
	BaseHUD->DrawTooltipWidget(bShow);
}

void ABaseTopDownPlayerPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ABaseTopDownPlayerPawn::CacheBaseHUD()
{
	const APlayerController* PlayerControllerRaw = GetLocalViewingPlayerController();
	if(PlayerControllerRaw)
	{
		BaseHUD = Cast<ABaseHUD>(PlayerControllerRaw->GetHUD());
	}
}

void ABaseTopDownPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	CacheBaseHUD();
}

void ABaseTopDownPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

#if KD_GRAPHIC_LOG
	DrawDebugSphere(GetWorld(), GetActorLocation(), 10.f, 12, FColor::Green);
#endif
}

//===== Begin IPlayerCameraMovementInterface
void ABaseTopDownPlayerPawn::MoveForward(float AxisValue)
{	
	if (MovementComponent && AxisValue)
	{
		const FVector MovementVector = GetActorForwardVector() * AxisValue * CameraComponent->GetCameraParamsData().CameraSpeed;

		OnOffsetUpdate(MovementVector);
	}
}

void ABaseTopDownPlayerPawn::MoveRight(float AxisValue)
{
	if(MovementComponent && AxisValue)
	{
		const FVector MovementVector = GetActorRightVector() * AxisValue * CameraComponent->GetCameraParamsData().CameraSpeed;

		OnOffsetUpdate(MovementVector);
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
//===== End IPlayerCameraMovementInterface

void ABaseTopDownPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	GetInteractionComponent()->SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseTopDownPlayerPawn::ServerUpdatePlayerPosition_Implementation(const FVector& Offset)
{
	OnOffsetUpdate(Offset);
	ClientUpdatePlayerPosition(Offset);
}

void ABaseTopDownPlayerPawn::ClientUpdatePlayerPosition_Implementation(const FVector& Offset)
{
	OnOffsetUpdate(Offset);
}

void ABaseTopDownPlayerPawn::OnOffsetUpdate(const FVector& Offset)
{
	MovementComponent->AddInputVector(Offset);
}

void ABaseTopDownPlayerPawn::SetCursorGridDecalComponentLocation(const FVector& NewLocation) const
{
	CursorGridDecalComponent->SetWorldLocation(NewLocation);
}
void ABaseTopDownPlayerPawn::SetCursorGridDecalSize(const float Size) const
{
	CursorGridDecalComponent->UpdateDecalSize(Size);
}