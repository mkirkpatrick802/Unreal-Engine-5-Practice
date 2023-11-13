#pragma once

#include "CoreMinimal.h"

class AHornet;

class PROJECT_STINGER_API Octree
{
public:

	static Octree* Create(FVector Center, float HalfWidth, int Depth = 1);
	// TODO: Make a cleanup function

	virtual void Insert(AHornet* Hornet) = 0;
	virtual int GetNumberOfContents() = 0;
	virtual void Clear() = 0;


	virtual void GetNeighbors(TArray<AHornet*>& Neighbors, AHornet* Hornet) = 0;

	virtual void DrawDebug(const UWorld* World) = 0;

	const int RESIZE_THRESHOLD = 5;
};