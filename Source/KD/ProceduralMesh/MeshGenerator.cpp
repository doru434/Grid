// Fill out your copyright notice in the Description page of Project Settings.


#include "KD/ProceduralMesh/MeshGenerator.h"

#include "LandscapeInfo.h"
#include "LandscapeInfoMap.h"
#include "ProceduralMeshComponent.h"

// Sets default values
AMeshGenerator::AMeshGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProceduralMeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMeshComponent"));
	ProceduralMeshComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AMeshGenerator::BeginPlay()
{
	Super::BeginPlay();
}

void AMeshGenerator::Build()
{
	FillVertices();
	FillTriangles();
	CreateMeshSection();
}

void AMeshGenerator::Destroy()
{
	ClearData();
	ClearMeshSection();
}

void AMeshGenerator::CreateMeshSection()
{
	ProceduralMeshComponent->CreateMeshSection(0, Vertices, Triangles, Normals, UV0, VertexColors, TArray<FProcMeshTangent>(), true);

 	ProceduralMeshComponent->SetMaterial(0, MaterialRef);
	ClearData();
}

void AMeshGenerator::ClearMeshSection()
{
	ProceduralMeshComponent->ClearMeshSection(0);
}

void AMeshGenerator::FillVertices()
{
	Vertices.Empty();

	for (int i = 0; i < SizeX; ++i)
	{
		for (int j = 0; j < SizeY; ++j)
		{
			Vertices.Add(FVector(i*Gap, j*Gap,0.f));
			Normals.Add(FVector::UpVector);

			const float NumberOfSquaresX = SizeX - 1;
			const float UVStepX = 1.f / NumberOfSquaresX;

			const float NumberOfSquaresY = SizeY - 1;
			const float UVStepY = 1.f / NumberOfSquaresY;

			UV0.Add(FVector2D(i * UVStepX, j * UVStepY));
			VertexColors.Add(FColor::White);
		}
	}
}

void AMeshGenerator::ColorSquare(int Root, int SquareSize)
{
	FColor Color = FColor::Red;

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			if (VertexColors.Num() > Root + i * SizeY + j)
			{
				VertexColors[Root + i * SizeY + j] = Color;
			}
		}
	}
}

void AMeshGenerator::FillTriangles()
{
	Triangles.Empty();

	for (int i = 0; i < SizeX-1; ++i)
	{
		for (int j = 0; j < SizeY-1; ++j)
		{
			Triangles.Add(i*SizeY + j);
			Triangles.Add(i*SizeY + j + 1);
			Triangles.Add((i+1)*SizeY + j + 1);
			Triangles.Add(i*SizeY + j);
			Triangles.Add((i + 1)*SizeY + j + 1);
			Triangles.Add((i + 1)*SizeY + j);
		}
	}
}

void AMeshGenerator::ClearData()
{
	Vertices.Empty();
	Triangles.Empty();
	Normals.Empty();
	UV0.Empty();
	VertexColors.Empty();
}


