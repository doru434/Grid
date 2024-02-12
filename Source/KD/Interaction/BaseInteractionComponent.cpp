// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInteractionComponent.h"

#include "InteractionInterface.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "GameFramework/HUD.h"
#include "KD/Player/BaseTopDownPlayerPawn.h"
#include "KD/Grid/GridWorldSubsystem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UBaseInteractionComponent::UBaseInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bAllowTickOnDedicatedServer = false;
}

void UBaseInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	ENetRole NetRole = OwnerPawn ? OwnerPawn->GetRemoteRole() : ROLE_None;

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
	if (!PlayerController)
	{
		TryPopulatePlayerController();
	}
	ensure(PlayerController);

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
// 	AActor* ActorWithInteractionInterface = nullptr;
// 	TArray<UActorComponent*> InteractedActorComponentsWithInteractionInterface;
// 
// 	if (ActorRaw->Implements<UInteractionInterface>())
// 	{
// 		ActorWithInteractionInterface = ActorRaw;
// 	}
// 
// 	InteractedActorComponentsWithInteractionInterface = ActorRaw->GetComponentsByInterface(UInteractionInterface::StaticClass());
// 
// 
// 	switch (InteractionState)
// 	{
// 		case EInteractionState::Initial:
// 		{
// 
// 			InteractionData.InitialHitData.HitResult = Hit;
// 			InteractionData.InitialHitData.Actor = ActorWithInteractionInterface;
// 			InteractionData.InitialHitData.ActorComponents = InteractedActorComponentsWithInteractionInterface;
// 
// 			break;
// 		}
// 		case EInteractionState::Final:
// 		{
// 			InteractionData.FinalHitData.HitResult = Hit;
// 			InteractionData.FinalHitData.Actor = ActorWithInteractionInterface;
// 			InteractionData.FinalHitData.ActorComponents = InteractedActorComponentsWithInteractionInterface;
// 
// 			break;
// 		}
// 		default:
// 			break;
// 	}
}

void UBaseInteractionComponent::ClearInteractionData()
{
	InteractionData = FInteractionData();
}

bool UBaseInteractionComponent::GetHitUnderMouse(FHitResult& HitResult) const
{
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

	if(GetHitUnderMouse(Hit))
	{
		ResolveHovering(Hit);
	}
}

void UBaseInteractionComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	ensure(PlayerInputComponent);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &UBaseInteractionComponent::OnInteractionPressed);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &UBaseInteractionComponent::OnInteractionReleased);
}

void UBaseInteractionComponent::OnInteractionPressed()
{
	InteractionData.OnInteractionEnd(this);

	CollectInteractionData(EInteractionState::Initial);
	
	InteractionData.OnInteractionStart(this);
}

void UBaseInteractionComponent::OnInteractionReleased()
{
	CollectInteractionData(EInteractionState::Final);

	InteractionData.OnInteractionEnd(this);	
}

void UBaseInteractionComponent::PupulateInteractionDataWithHoverData(FInteractionHitData& InteractionComponentHitData)
{
	ensure(HoverData.IsValid());

	InteractionComponentHitData.Actor = HoverData.HoverInteractionHitData.Actor;
	InteractionComponentHitData.ActorComponents = HoverData.HoverInteractionHitData.ActorComponents;
	InteractionComponentHitData.HitResult = HoverData.HoverInteractionHitData.HitResult;
}

void UBaseInteractionComponent::ResolveHovering(const FHitResult& Hit)
{
	UnhoverPrevious();

	PupulateHoverData(Hit);

	//Hover
	if (HoverData.IsValid())
	{
		HoverData.OnMouseHoverBegining(this);
	}
}

void UBaseInteractionComponent::PupulateHoverData(const FHitResult& Hit)
{
	ensure(Hit.bBlockingHit);

	HoverData = FHoverData(Hit);
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

