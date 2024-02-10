// Fill out your copyright notice in the Description page of Project Settings.


#include "KD/Animation/KDAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

void UKDAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	if ( ! OwnerData.IsValid())
	{
		InitOwnerData();
	}
}

void UKDAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OwnerData.IsValid())
	{
		const UPawnMovementComponent* PawnMovementComponentRaw = OwnerData.GetOwnerMovementComponentChecked();
		LocomotionData.Velocity = PawnMovementComponentRaw->Velocity;
		LocomotionData.GroundSpeed = LocomotionData.Velocity.Size2D();

		LocomotionData.bShouldMove = LocomotionData.GroundSpeed > 3.f && !FMath::IsNearlyZero(PawnMovementComponentRaw->GetLastInputVector().SizeSquared());

		LocomotionData.bIsFalling = PawnMovementComponentRaw->IsFalling();
	}
}

void UKDAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UKDAnimInstance::PostInitProperties()
{
	Super::PostInitProperties();
}

void UKDAnimInstance::InitOwnerData()
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetSkelMeshComponent()->GetOwner());
	check(OwnerCharacter);

	OwnerData.SetOwner(OwnerCharacter);
	OwnerData.SetOwnerMovementComponent(OwnerCharacter->GetMovementComponent());
}

///////////////
// FOwnerData
///////////////
ACharacter* FOwnerData::GetOwnerCharacterChecked() const
{
	ACharacter* OwnerCharacterRaw = OwnerCharacter.Get();
	check(OwnerCharacterRaw);

	return OwnerCharacterRaw;
}

UPawnMovementComponent* FOwnerData::GetOwnerMovementComponentChecked() const
{
	UPawnMovementComponent* OwnerMovementComponentRaw = OwnerMovementComponent.Get();
	check(OwnerMovementComponentRaw);

	return OwnerMovementComponentRaw;
}

void FOwnerData::SetOwner(ACharacter* InOwnerCharacter)
{
	OwnerCharacter = MakeWeakObjectPtr(InOwnerCharacter);
}

void FOwnerData::SetOwnerMovementComponent(UPawnMovementComponent* InOwnerMovementComponent)
{
	OwnerMovementComponent = MakeWeakObjectPtr(InOwnerMovementComponent);
}

bool FOwnerData::IsValid() const
{
	return OwnerCharacter.IsValid() && OwnerMovementComponent.IsValid();
}

///////////////
// ~FOwnerData
///////////////