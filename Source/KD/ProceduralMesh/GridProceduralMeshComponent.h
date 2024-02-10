// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "GridProceduralMeshComponent.generated.h"

class UMaterialInterface;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KD_API UGridProceduralMeshComponent : public UProceduralMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGridProceduralMeshComponent(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, CallInEditor)
	void Build();

	UFUNCTION(BlueprintCallable, CallInEditor)
	void Destroy();

	UFUNCTION(BlueprintCallable)
	void GenerateMeshSection();

	UFUNCTION(BlueprintCallable)
	void FillVertices();

	void ColorSquare(int Root, int SquareSize);

	UFUNCTION(BlueprintCallable)
	void FillTriangles();

	UFUNCTION(BlueprintCallable)
	void ClearData();

protected:
	// ActorComponent
	virtual void BeginPlay() override;
	// ~ActorComponent

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
	int32 NumberOfCellsX;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 NumberOfCellsY;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float CellSize;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UMaterialInterface> MaterialRef;

private:

};
