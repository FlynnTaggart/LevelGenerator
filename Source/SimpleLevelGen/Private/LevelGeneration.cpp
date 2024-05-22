// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelGeneration.h"


TArray<FAdjacencyArr> ULevelGeneration::GenerateLevelsStruct(int LevelsCount)
{
    TArray<GenEdge> a;

    for (int i = 0; i < LevelsCount; ++i) {
        a.Add(GenEdge{ i, TSet<int>(), rand() % 3 + 2 });
    }

    TArray<FAdjacencyArr> G;
    G.Init(FAdjacencyArr{ TArray<int>() }, LevelsCount);

    for (int i = 0; i < LevelsCount; ++i) {
        int conns = a[i].maxConns;
        GenerateBranch(G, a, i, conns);
    }

    
    
    for (int i = G.Num() -1 ; i >= 0; i--){
        FString s = FString::FromInt(i) + " --> ";
        for (int j = 0; j < G[i].Adjacencies.Num(); ++j) {
            s += FString::FromInt(G[i].Adjacencies[j]) + " ";
        }
        GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("%s"), *s));
    }

    GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, TEXT("Generated graph:"));

	return G;
}

void ULevelGeneration::GenerateBranch(TArray<FAdjacencyArr>& G, TArray<GenEdge>& initVerticies, int cur, int conns)
{
    for (int i = 0; i < conns; ++i) {
        if (initVerticies[cur].visitedBy.Num() >= initVerticies[cur].maxConns) {
            continue;
        }

        int picked = FMath::Rand() % initVerticies.Num();

        while (picked == cur) {
            picked = FMath::Rand() % initVerticies.Num();
        }

        int pickCnt = 1;

        while (initVerticies[cur].visitedBy.Find(picked) != nullptr
            || initVerticies[picked].visitedBy.Num() >= initVerticies[picked].maxConns) {
            picked = FMath::Rand() % initVerticies.Num();
            while (picked == cur) {
                picked = FMath::Rand() % initVerticies.Num();
            }


            pickCnt++;
            if (pickCnt > 3) {
                break;
            }
        }

        if (pickCnt == 4) {
            continue;
        }


        initVerticies[cur].visitedBy.Add(picked);
        initVerticies[picked].visitedBy.Add(cur);

        G[cur].Adjacencies.Add(picked);
        G[picked].Adjacencies.Add(cur);
    }
}
