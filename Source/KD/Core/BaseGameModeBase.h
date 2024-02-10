// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseGameModeBase.generated.h"

UCLASS()
class KD_API ABaseGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:


protected:
	virtual void BeginPlay() override;

private:

};
