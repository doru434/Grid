// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation\AnimInstance.h"
#include "KDAnimInstance.generated.h"

class ACharacter;
class AController;
class UPawnMovementComponent;

USTRUCT(BlueprintType)
struct FLocomotionData
{
	GENERATED_USTRUCT_BODY()

	FLocomotionData()
		: Velocity(FVector::ZeroVector)
		, GroundSpeed(0)
		, bShouldMove(false)
		, bIsFalling(false)
	{
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector Velocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float GroundSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bShouldMove;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsFalling;
};

USTRUCT(BlueprintType)
struct FOwnerData
{
	GENERATED_USTRUCT_BODY()

	FOwnerData()
		: OwnerCharacter(nullptr)
		, OwnerMovementComponent(nullptr)
	{
	}

	ACharacter* GetOwnerCharacterChecked() const;

	UPawnMovementComponent* GetOwnerMovementComponentChecked() const;

	void SetOwner(ACharacter* InOwnerCharacter);

	void SetOwnerMovementComponent(UPawnMovementComponent* InOwnerMovementComponent);

	bool IsValid() const;

private:
	UPROPERTY(EditAnywhere)
	TWeakObjectPtr<ACharacter> OwnerCharacter;

	UPROPERTY(EditAnywhere)
	TWeakObjectPtr<UPawnMovementComponent> OwnerMovementComponent;
};


/**
 * 
 */
UCLASS()
class KD_API UKDAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FLocomotionData	LocomotionData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FOwnerData	OwnerData;

	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

	virtual void PostInitProperties() override;


	void InitOwnerData();
};
