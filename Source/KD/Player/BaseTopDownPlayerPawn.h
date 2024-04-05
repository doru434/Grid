// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "KD/Camera/PlayerCameraMovementInterface.h"
#include "KD/Grid/GridComponent.h"
#include "BaseTopDownPlayerPawn.generated.h"

class UBaseInteractionComponent;
class UBaseCameraComponent;
class UGridDecalComponent;
class USceneComponent;
class UFloatingPawnMovement;

UCLASS(Abstract)
class KD_API ABaseTopDownPlayerPawn : public APawn, public IPlayerCameraMovementInterface
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UBaseInteractionComponent* GetInteractionComponent() const {return InteractionComponent;}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UBaseCameraComponent* GetCameraComponent() const {return CameraComponent;}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UGridDecalComponent* GetCursorGridDecalComponent() const {return CursorGridDecalComponent;}

	void UpdatePlayerCursor(const bool bShow, const FVector& NewLocation = FVector::ZeroVector, const float Size = 0.f) const;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Begin IPlayerCameraMovementInterface
	virtual void MoveForward(float AxisValue) override;
	virtual void MoveRight(float AxisValue) override;
	virtual void Rotate(float AxisValue) override;
	virtual void Zoom(float AxisValue) override;
	virtual void ResetRotation() override;
	virtual void MouseCameraMovementActivation() override;
	virtual void MouseCameraMovementDeactivation() override;
	// End IPlayerCameraMovementInterface

	// Begin APawn
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	// End APawn

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBaseInteractionComponent> InteractionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CustomCamera")
	TObjectPtr<UBaseCameraComponent> CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid")
	TObjectPtr<UGridDecalComponent> CursorGridDecalComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CustomCamera")
	float CameraMovementSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UFloatingPawnMovement> MovementComponent;

	UFUNCTION(Server, Unreliable)
	void ServerUpdatePlayerPosition(const FVector& Offset);

	UFUNCTION(Client, Unreliable)
	void ClientUpdatePlayerPosition(const FVector& Offset);

	void OnOffsetUpdate(const FVector& Offset);

private:
	void SetCursorGridDecalComponentLocation(const FVector& NewLocation) const;
	void SetCursorGridDecalSize(const float Size) const;
};
