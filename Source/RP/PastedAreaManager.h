#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PastedAreaManager.generated.h"

UCLASS()
class RP_API APastedAreaManager : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APastedAreaManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
