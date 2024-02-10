// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridComponent.h"
#include "GameFramework/Actor.h"
#include "GridTypes.h"
#include "GridManager.generated.h"

class UBaseGridLayout;

UCLASS()
class KD_API AGridManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGridManager();

	// AActor interface
	virtual void Tick(float DeltaTime) override;
	// End AActor interface

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UGridComponent* GetGridComponent() const { return  GridComponent;}
	
protected:
	virtual void BeginPlay() override;
	// End AActor interface

private:

	UPROPERTY()
	TObjectPtr<UGridComponent> GridComponent;
};
	



