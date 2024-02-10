// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Test.generated.h"

USTRUCT()
struct FMyStructInner
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = MyStructCategory)
	float Scale;

	UPROPERTY(EditAnywhere, Category = MyStructCategory)
	float ScaleB;
};

USTRUCT()
struct FMyStructB
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = MyStructBCategory)
	int32 Age;

	UPROPERTY(EditAnywhere, Category = MyStructBCategory)
	FColor Color;
};

USTRUCT()
struct FMyStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = MyStructCategory)
	int32 Number;

	UPROPERTY(EditAnywhere, Category = MyStructCategory)
	FVector Vector;

	UPROPERTY(EditAnywhere, Category = MyStructCategory)
	FMyStructInner MyStructInner;
};

UCLASS(Blueprintable)
class RP_API UTest : public UObject
{
	GENERATED_BODY()
//meta = (ShowOnlyInnerProperties)
	UPROPERTY(EditAnywhere, Category = Structs, meta = (ShowOnlyInnerProperties))
	FMyStruct MyStruct;

	UPROPERTY(EditAnywhere, Category = Structs, meta = (ShowOnlyInnerProperties))
	FMyStructB MyStructB;

	UPROPERTY(EditAnywhere, Category = Structs, meta = (ShowOnlyInnerProperties))
	FMyStructInner MyStructInner;

};
