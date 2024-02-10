// Fill out your copyright notice in the Description page of Project Settings.


#include "KD/Characters/AI/KDAIController.h"

#include "BehaviorTree/BehaviorTree.h"

void AKDAIController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if(BehaviorTree.Get())
	{
		RunBehaviorTree(BehaviorTree.Get());
	}
}
