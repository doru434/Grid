// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Components/SceneComponent.h>

#include "Engine/DataTable.h"
#include "BaseCameraComponent.generated.h"

class UCameraComponent;
class USpringArmComponent;

USTRUCT(BlueprintType)
struct FCameraParamsData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	uint8 AllowRotation:1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bScreenMarginMovement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ScreenMargin;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CameraSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float RotationSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CameraZoomingSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxCameraHeight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MinCameraHeight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FRotator MinCameraRotation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FRotator MaxCameraRotation;

	FCameraParamsData()
		: AllowRotation(true)
		, bScreenMarginMovement(false)
		, ScreenMargin(20.f)
		, CameraSpeed(5.f)
		, RotationSpeed(1.f)
		, CameraZoomingSpeed(5.f)
		, MaxCameraHeight(400.f)
		, MinCameraHeight(50.f)
		, MinCameraRotation(FRotator( -30.f, 0.f, 0.f))
		, MaxCameraRotation(FRotator( -75.f, 0.f, 0.f))
	{

	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KD_API UBaseCameraComponent : public USceneComponent
{
	GENERATED_UCLASS_BODY()
public:	
	//USceneComponent interface
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void OnRegister() override;
	virtual void BeginPlay() override;
	//End of USceneComponent interface

	void MouseCameraMovementActivation();

	void MouseCameraMovementDeactivation();

	void Rotate(float AxisValue);
	void Zoom(float AxisValue) const;
	void ResetRotation();

	UFUNCTION()
	FORCEINLINE FCameraParamsData& GetCameraParamsData();

	UFUNCTION()
	void MoveCameraByMouse() const;

	UFUNCTION()
	void ZoomCameraByMouse() const;

	UFUNCTION()
	void RotateCameraByMouse();

protected:
	UPROPERTY()
	uint8 bCameraMovementMouseButtonPressed:1;

	UPROPERTY()
	FVector2D BaseMousePosition = FVector2D(0.f, 0.f);

	UPROPERTY()
	FVector2D DeltaMousePosition = FVector2D(0.f, 0.f);

	UPROPERTY(EditDefaultsOnly, Category = "CustomCamera")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, Category = "CustomCamera")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditDefaultsOnly, Category = "CustomCamera")
	FCameraParamsData CameraParamsData;
private:


};
