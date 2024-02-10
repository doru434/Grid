#include "PastedAreaManager.h"

// Sets default values
APastedAreaManager::APastedAreaManager()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APastedAreaManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APastedAreaManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
