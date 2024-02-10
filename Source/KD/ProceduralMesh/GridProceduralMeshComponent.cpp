// Fill out your copyright notice in the Description page of Project Settings.


#include "GridProceduralMeshComponent.h"

UGridProceduralMeshComponent::UGridProceduralMeshComponent(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UGridProceduralMeshComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UGridProceduralMeshComponent::Build()
{
	FillVertices();
	FillTriangles();
	GenerateMeshSection();
}

void UGridProceduralMeshComponent::Destroy()
{
	ClearData();
	ClearMeshSection(0);
}

void UGridProceduralMeshComponent::GenerateMeshSection()
{
	CreateMeshSection(0, Vertices, Triangles, Normals, UV0, VertexColors, TArray<FProcMeshTangent>(), true);

	SetMaterial(0, MaterialRef);
	ClearData();
}

void UGridProceduralMeshComponent::FillVertices()
{
	Vertices.Empty();

	for (int i = 0; i < NumberOfCellsX; ++i)
	{
		for (int j = 0; j < NumberOfCellsY; ++j)
		{
			Vertices.Add(FVector(i * CellSize, j * CellSize, 0.f));
			Normals.Add(FVector::UpVector);

			const float NumberOfSquaresX = NumberOfCellsX - 1;
			const float UVStepX = 1.f / NumberOfSquaresX;

			const float NumberOfSquaresY = NumberOfCellsY - 1;
			const float UVStepY = 1.f / NumberOfSquaresY;

			UV0.Add(FVector2D(i * UVStepX, j * UVStepY));
			VertexColors.Add(FColor::White);
		}
	}
}

void UGridProceduralMeshComponent::ColorSquare(int Root, int SquareSize)
{
	FColor Color = FColor::Red;

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			if (VertexColors.Num() > Root + i * NumberOfCellsY + j)
			{
				VertexColors[Root + i * NumberOfCellsY + j] = Color;
			}
		}
	}
}

void UGridProceduralMeshComponent::FillTriangles()
{
	Triangles.Empty();

	for (int i = 0; i < NumberOfCellsX - 1; ++i)
	{
		for (int j = 0; j < NumberOfCellsY - 1; ++j)
		{
			Triangles.Add(i * NumberOfCellsY + j);
			Triangles.Add(i * NumberOfCellsY + j + 1);
			Triangles.Add((i + 1) * NumberOfCellsY + j + 1);
			Triangles.Add(i * NumberOfCellsY + j);
			Triangles.Add((i + 1) * NumberOfCellsY + j + 1);
			Triangles.Add((i + 1) * NumberOfCellsY + j);
		}
	}
}

void UGridProceduralMeshComponent::ClearData()
{
	Vertices.Empty();
	Triangles.Empty();
	Normals.Empty();
	UV0.Empty();
	VertexColors.Empty();
}
