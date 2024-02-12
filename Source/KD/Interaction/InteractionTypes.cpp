// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractionTypes.h"
#include "BaseInteractionComponent.h"

//===========
// FInteractionHitData
//===========
void FInteractionHitData::Reset()
{
	HitResult = FHitResult();
	Actor = nullptr;
	ActorComponents.Reset();
}

bool FInteractionHitData::IsValid() const
{
	return HitResult.GetActor() && (Actor || !ActorComponents.IsEmpty());
}


//===========
// FHoverData
//===========
bool FHoverData::IsValid() const
{
	return HoverInteractionHitData.IsValid();
}

void FHoverData::ClearData()
{
	HoverInteractionHitData.Reset();
}

void FHoverData::OnMouseHoverBegining(const UBaseInteractionComponent* InteractionComponent)
{
	if (HoverInteractionHitData.Actor->Implements<UInteractionInterface>())
	{
		IInteractionInterface::Execute_OnMouseHoverBegining(HoverInteractionHitData.Actor, InteractionComponent, HoverInteractionHitData.HitResult);
	}

	for (UActorComponent* Comp : HoverInteractionHitData.ActorComponents)
	{
		IInteractionInterface::Execute_OnMouseHoverBegining(Comp, InteractionComponent, HoverInteractionHitData.HitResult);
	}	
}

void FHoverData::OnMouseHoverEnd(const UBaseInteractionComponent* InteractionComponent)
{
	AActor* HoveredActor = HoverInteractionHitData.Actor;
	if (HoveredActor)
	{
		if (HoveredActor->Implements<UInteractionInterface>())
		{
			IInteractionInterface::Execute_OnMouseHoverEnd(HoveredActor, InteractionComponent, HoverInteractionHitData.HitResult);
		}

		for (UActorComponent* Comp : HoverInteractionHitData.ActorComponents)
		{
			if (Comp)
			{
				IInteractionInterface::Execute_OnMouseHoverEnd(Comp, InteractionComponent, HoverInteractionHitData.HitResult);
			}
		}
	}
}

//===========
// FInteractionData
//===========
bool FInteractionData::IsValid() const
{
	return InitialHitData.IsValid() && FinalHitData.IsValid();
}

void FInteractionData::ClearData()
{
	InitialHitData.Reset();
	FinalHitData.Reset();
}

void FInteractionData::OnInteractionStart(const UBaseInteractionComponent* InteractionComponent)
{
	if (!InitialHitData.IsValid())
	{
		return;
	}

	if (InitialHitData.Actor && InitialHitData.Actor->Implements<UInteractionInterface>())
	{
		IInteractionInterface::Execute_OnInteractionBegining(InitialHitData.Actor, InteractionComponent, InitialHitData.HitResult);
	}

	for (UActorComponent* Comp : InitialHitData.ActorComponents)
	{
		if (Comp)
		{
			IInteractionInterface::Execute_OnInteractionBegining(Comp, InteractionComponent, InitialHitData.HitResult);
		}
	}

}

void FInteractionData::OnInteractionEnd(const UBaseInteractionComponent* InteractionComponent)
{
	if (!FinalHitData.IsValid())
	{
		return;
	}

	if (InitialHitData.Actor)
	{
		if (InitialHitData.Actor && InitialHitData.Actor->Implements<UInteractionInterface>())
		{
			IInteractionInterface::Execute_OnInteractionEnd(InitialHitData.Actor, InteractionComponent, InitialHitData.HitResult);
		}

		for (UActorComponent* Comp : InitialHitData.ActorComponents)
		{
			if (Comp)
			{
				IInteractionInterface::Execute_OnInteractionEnd(Comp, InteractionComponent, InitialHitData.HitResult);
			}
		}
	}

	ClearData();
}