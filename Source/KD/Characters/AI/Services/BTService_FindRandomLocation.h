
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_FindRandomLocation.generated.h"

class UBehaviorTree;


struct FBTFindRandomLocationMemory
{
	FVector Location;

	void Reset()
	{
		Location = FVector::ZeroVector;
	}
};

UCLASS()
class KD_API UBTService_FindRandomLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()

protected:

	UBTService_FindRandomLocation(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual uint16 GetInstanceMemorySize() const override { return sizeof(FBTFindRandomLocationMemory); }
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual FString GetStaticDescription() const override;

	EBlackboardNotificationResult OnBlackboardKeyValueChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID);

#if WITH_EDITOR
	virtual FName GetNodeIconName() const override;
#endif // WITH_EDITOR
};
