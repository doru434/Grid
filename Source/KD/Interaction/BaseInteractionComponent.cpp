// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInteractionComponent.h"

#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "GameFramework/HUD.h"
#include "KD/Player/BaseTopDownPlayerPawn.h"
#include "KD/Grid/GridWorldSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Logging/StructuredLog.h"

// Sets default values for this component's properties
UBaseInteractionComponent::UBaseInteractionComponent()
	: InteractionComponentState(EInteractionComponentState::Basic)
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bAllowTickOnDedicatedServer = false;
}

void UBaseInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	const APawn* OwnerPawn = Cast<APawn>(GetOwner());
	const ENetRole NetRole = OwnerPawn ? OwnerPawn->GetRemoteRole() : ROLE_None;

	if (!OwnerPawn || !(NetRole == ROLE_AutonomousProxy || NetRole == ROLE_SimulatedProxy))
	{
		PrimaryComponentTick.SetTickFunctionEnable(false);
		return;
	}

	TryPopulatePlayerController();

	BaseTopDownPlayerPawn = Cast<ABaseTopDownPlayerPawn>(GetOwner());
	ensure(BaseTopDownPlayerPawn);
}

void UBaseInteractionComponent::BeginDestroy()
{
	Super::BeginDestroy();
}

void UBaseInteractionComponent::CollectInteractionData(EInteractionState InteractionState)
{
	if (HoverData.IsValid())
	{
		switch (InteractionState)
		{
		case EInteractionState::Initial:
			PupulateInteractionDataWithHoverData(InteractionData.InitialHitData);
			break;
		case EInteractionState::Final:
			PupulateInteractionDataWithHoverData(InteractionData.FinalHitData);
			break;
		default:
			break;
		}
	}
}

void UBaseInteractionComponent::ClearInteractionData()
{
	InteractionData = FInteractionData();
}

bool UBaseInteractionComponent::GetHitUnderMouse(FHitResult& HitResult) const
{
	if (!PlayerController)
	{
		return false;
	}

	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(PlayerController->Player);
	if (LocalPlayer && LocalPlayer->ViewportClient)
	{
		FVector2D MousePosition;
		if (LocalPlayer->ViewportClient->GetMousePosition(MousePosition))
		{
			const FCollisionQueryParams CollisionQueryParams(SCENE_QUERY_STAT(ClickableTrace), false );

			// Early out if we clicked on a HUD hitbox
			if (PlayerController->GetHUD() != nullptr && PlayerController->GetHUD()->GetHitBoxAtCoordinates(MousePosition, true))
			{
				return false;
			}

			FVector WorldOrigin;
			FVector WorldDirection;
			if (UGameplayStatics::DeprojectScreenToWorld(PlayerController, MousePosition,  WorldOrigin, WorldDirection) == true)
			{
#ifdef WITH_EDITOR
				DrawDebugLine(GetWorld(), WorldOrigin, WorldOrigin + WorldDirection * 15000.0, FColor::Red);
#endif
				return GetWorld()->LineTraceSingleByChannel(HitResult, WorldOrigin, WorldOrigin + WorldDirection * 15000.0, ECollisionChannel::ECC_WorldDynamic, CollisionQueryParams);
			}
		}
	}

	return false;
}

// Called every frame
void UBaseInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FHitResult Hit;

	if (GetHitUnderMouse(Hit))
	{
		ResolveHovering(Hit);
	}

	switch (InteractionComponentState)
	{
	case EInteractionComponentState::Basic:
	{
		break;
	}
	case EInteractionComponentState::Selecting:
	{
		CollectInteractionData(EInteractionState::Final);
		break;
	}
	case EInteractionComponentState::Building:
		break;
	default:
		break;
	}
}

void UBaseInteractionComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	ensure(PlayerInputComponent);

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (Input)
	{
		Input->BindAction(MainAction, ETriggerEvent::Started, this, &UBaseInteractionComponent::OnMainActionPressed);
		Input->BindAction(MainAction, ETriggerEvent::Completed, this, &UBaseInteractionComponent::OnMainActionReleased);

		Input->BindAction(BuildModeAction, ETriggerEvent::Triggered, this, &UBaseInteractionComponent::OnBuildModePressed);
	}
}

void UBaseInteractionComponent::OnMainActionPressed(const FInputActionValue& Value)
{
	InteractionData.OnInteractionEnd(this);

	CollectInteractionData(EInteractionState::Initial);
	
	InteractionData.OnInteractionStart(this);
}

void UBaseInteractionComponent::OnMainActionReleased(const FInputActionValue& Value)
{

}

void UBaseInteractionComponent::OnBuildModePressed(const FInputActionValue& Value)
{

}

void UBaseInteractionComponent::PupulateInteractionDataWithHoverData(FInteractionHitData& InteractionComponentHitData)
{
	ensure(HoverData.IsValid());

	InteractionComponentHitData.InteractionInterfaceActor = HoverData.HoverInteractionHitData.InteractionInterfaceActor;
	InteractionComponentHitData.ActorComponent = HoverData.HoverInteractionHitData.ActorComponent;
	InteractionComponentHitData.HitResult = HoverData.HoverInteractionHitData.HitResult;
}

void UBaseInteractionComponent::ResolveHovering(const FHitResult& Hit)
{
	const FHoverData TempHoverData(Hit);

	if (Hit.bBlockingHit && HasHoverChanged(TempHoverData))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hovering Changed"));
		UnhoverPrevious();

		HoverData = TempHoverData;

		//Hover
		if (HoverData.IsValid())
		{
			HoverData.OnMouseHoverBegining(this);
		}
	}
}

bool UBaseInteractionComponent::HasHoverChanged(const FHoverData& InHoverData) const
{
	if(const bool bNewHoverDataValid = InHoverData.IsValid())
	{
		return HoverData.IsValid() ? !HoverData.IsEqual(InHoverData) : true;
	}
	
	return HoverData.IsValid() ? true : false;
}

void UBaseInteractionComponent::UnhoverPrevious()
{
	HoverData.OnMouseHoverEnd(this);
	HoverData.ClearData();
}

void UBaseInteractionComponent::TryPopulatePlayerController()
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn)
	{
		PlayerController = Cast<APlayerController>(OwnerPawn->GetController());
	}
}

