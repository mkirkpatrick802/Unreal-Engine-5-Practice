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

	const int GROW_THRESHOLD = 6;
	const int SHRINK_THRESHOLD = 3;
	const int MAX_DEPTH = 3;

protected:

	// This is the index for where this class is in the parents octree, ie if its 3 then its the third child for the parent node
	// If Index is -1 then the node is the root and cannot shrink;
	int Index = -1;
	int CurrentDepth = 0;
};