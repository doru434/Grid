// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractionTypes.h"

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

void FHoverData::Hover(UBaseInteractionComponent* BaseInteractionComponent)
{
	
	if (HoverInteractionHitData.Actor->Implements<UInteractionInterface>())
	{
		IInteractionInterface::Execute_OnMouseHoverStart(HoverInteractionHitData.Actor, BaseInteractionComponent, HoverInteractionHitData.HitResult);
	}

	for (UActorComponent* Comp : HoverInteractionHitData.ActorComponents)
	{
		IInteractionInterface::Execute_OnMouseHoverStart(Comp, BaseInteractionComponent, HoverInteractionHitData.HitResult);
	}	
}

void FHoverData::Unhover(UBaseInteractionComponent* BaseInteractionComponent)
{
	AActor* HoveredActor = HoverInteractionHitData.Actor;
	if (HoveredActor)
	{
		if (HoveredActor->Implements<UInteractionInterface>())
		{
			IInteractionInterface::Execute_OnMouseHoverFinished(HoveredActor, BaseInteractionComponent, HoverInteractionHitData.HitResult);
		}

		for (UActorComponent* Comp : HoverInteractionHitData.ActorComponents)
		{
			if (Comp)
			{
				IInteractionInterface::Execute_OnMouseHoverFinished(Comp, BaseInteractionComponent, HoverInteractionHitData.HitResult);
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