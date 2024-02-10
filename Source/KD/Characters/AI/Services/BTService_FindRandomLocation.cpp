// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_FindRandomLocation.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

UBTService_FindRandomLocation::UBTService_FindRandomLocation(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Find Random Location";
	
	bTickIntervals = false;

	INIT_SERVICE_NODE_NOTIFY_FLAGS();

	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_FindRandomLocation, BlackboardKey));
}

void UBTService_FindRandomLocation::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
}

void UBTService_FindRandomLocation::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);
}

FString UBTService_FindRandomLocation::GetStaticDescription() const
{
	FString KeyDesc("invalid");
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
	{
		KeyDesc = BlackboardKey.SelectedKeyName.ToString();
	}

	return FString::Printf(TEXT("Set default focus to %s"), *KeyDesc);
}

EBlackboardNotificationResult UBTService_FindRandomLocation::OnBlackboardKeyValueChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID)
{
	return EBlackboardNotificationResult::ContinueObserving;
}

#if WITH_EDITOR
FName UBTService_FindRandomLocation::GetNodeIconName() const
{
	return FName("BTEditor.Graph.BTNode.Service.DefaultFocus.Icon");
}
#endif	// WITH_EDITOR
