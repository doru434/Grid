// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/MaterialInterface.h"
#include "PADecalActor.generated.h"

class UPADecalComponent;

UCLASS()
class KD_API APADecalActor : public AActor
{
	GENERATED_BODY()

public:
	APADecalActor();

	// AActor interface
	virtual void Tick(float DeltaTime) override;
	virtual void BeginDestroy() override;
	// End AActor interface

	// 	UFUNCTION(BlueprintCallable)
// 	void SetDecalMaterial(UMaterialInterface* MaterialInterface);

//	void Init()
protected:
	virtual void BeginPlay() override;
	// End AActor interface

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPADecalComponent> PADecalComponent;

private:

};
