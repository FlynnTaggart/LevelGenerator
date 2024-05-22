// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LevelGeneration.generated.h"


USTRUCT(BlueprintType)
struct FAdjacencyArr
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> Adjacencies;
};

struct GenEdge {
	int num;
	TSet<int> visitedBy;
	int maxConns;
};

/**
 * 
 */
UCLASS()
class SIMPLELEVELGEN_API ULevelGeneration : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "GenerateLevelsStruct")
	static TArray<FAdjacencyArr> GenerateLevelsStruct(int LevelsCount);

	static void GenerateBranch(TArray<FAdjacencyArr>& G, TArray<GenEdge>& initVerticies, int cur, int conns);
};
