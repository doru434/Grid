// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractionTypes.h"
#include "BaseInteractionComponent.h"

//===========
// FInteractionHitData
//===========
void FInteractionHitData::Reset()
{
	HitResult = FHitResult();
	InteractionInterfaceActor = nullptr;
	ActorComponent = nullptr;
}

bool FInteractionHitData::IsValid() const
{
	return HitResult.GetActor() && (InteractionInterfaceActor || ActorComponent);
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
	if (HoverInteractionHitData.InteractionInterfaceActor)
	{
		IInteractionInterface::Execute_OnMouseHoverBegining(HoverInteractionHitData.InteractionInterfaceActor, InteractionComponent, HoverInteractionHitData.HitResult);
	}

	if(HoverInteractionHitData.ActorComponent)
	{
		IInteractionInterface::Execute_OnMouseHoverBegining(HoverInteractionHitData.ActorComponent, InteractionComponent, HoverInteractionHitData.HitResult);
	}	
}

void FHoverData::OnMouseHoverEnd(const UBaseInteractionComponent* InteractionComponent)
{
	if (HoverInteractionHitData.InteractionInterfaceActor)
	{
		IInteractionInterface::Execute_OnMouseHoverEnd(HoverInteractionHitData.InteractionInterfaceActor, InteractionComponent, HoverInteractionHitData.HitResult);
	}

	if(HoverInteractionHitData.ActorComponent)
	{
		IInteractionInterface::Execute_OnMouseHoverEnd(HoverInteractionHitData.ActorComponent, InteractionComponent, HoverInteractionHitData.HitResult);
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

	if (InitialHitData.InteractionInterfaceActor && InitialHitData.InteractionInterfaceActor->Implements<UInteractionInterface>())
	{
		IInteractionInterface::Execute_OnInteractionBegining(InitialHitData.InteractionInterfaceActor, InteractionComponent, InitialHitData.HitResult);
	}

	if (InitialHitData.ActorComponent)
	{
		IInteractionInterface::Execute_OnInteractionBegining(InitialHitData.ActorComponent, InteractionComponent, InitialHitData.HitResult);
	}

}

void FInteractionData::OnInteractionEnd(const UBaseInteractionComponent* InteractionComponent)
{
	if (!InitialHitData.IsValid())
	{
		return;
	}

	if (InitialHitData.InteractionInterfaceActor && InitialHitData.InteractionInterfaceActor->Implements<UInteractionInterface>())
	{
		IInteractionInterface::Execute_OnInteractionEnd(InitialHitData.InteractionInterfaceActor, InteractionComponent, InitialHitData.HitResult);
	}

	if (InitialHitData.ActorComponent)
	{
		IInteractionInterface::Execute_OnInteractionEnd(InitialHitData.ActorComponent, InteractionComponent, InitialHitData.HitResult);
	}

	ClearData();
}