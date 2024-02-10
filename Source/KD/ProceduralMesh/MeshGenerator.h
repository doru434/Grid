// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LandscapeDataAccess.h"
#include "LandscapeProxy.h"
#include "MeshGenerator.generated.h"

class ULandscapeInfoMap;
class ULandscapeInfo;
class UProceduralMeshComponent;

UCLASS()
class KD_API AMeshGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeshGenerator();

	UFUNCTION(BlueprintCallable, CallInEditor)
	void Build();

	UFUNCTION(BlueprintCallable, CallInEditor)
	void Destroy();

	UFUNCTION(BlueprintCallable)
	void CreateMeshSection();

	UFUNCTION(BlueprintCallable)
	void ClearMeshSection();

	UFUNCTION(BlueprintCallable)
	void FillVertices();

	void ColorSquare(int Root, int SquareSize);

	UFUNCTION(BlueprintCallable)
	void FillTriangles();

	UFUNCTION(BlueprintCallable)
	void ClearData();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)//, meta = (MakeEditWidget = true))
	TArray<FVector> Vertices;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<int32> Triangles;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FVector> Normals;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FVector2D> UV0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FColor> VertexColors;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 SizeX;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 SizeY;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Gap;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UMaterialInterface> MaterialRef;

private:
	UPROPERTY()
	TObjectPtr<UProceduralMeshComponent> ProceduralMeshComponent;
};
