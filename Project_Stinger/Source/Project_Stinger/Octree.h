#pragma once

#include "CoreMinimal.h"

class AHornet;

enum NodeType
{
	Null,
	Root,
	Node,
	Leaf
};

class PROJECT_STINGER_API Octree
{
public:

	NodeType Type = Null;

	static Octree* Create(const FVector& Center, float HalfWidth, int Depth = 1);
	// TODO: Make a cleanup function

	virtual void Insert(AHornet* Hornet) = 0;
	virtual TArray<AHornet*> GetHornets() = 0;
	virtual void Clear() = 0;

	void SetDepth(const int Current) { CurrentDepth = Current + 1; }

	virtual void Resize() = 0;
	virtual void GetNeighbors(TArray<AHornet*>& Neighbors, AHornet* Hornet) = 0;

	virtual void DrawDebug(const UWorld* World) = 0;

	const int RESIZE_THRESHOLD = 3;
	const int MAX_DEPTH = 3;

protected:

	int CurrentDepth = 1;

private:

	inline static bool RootSet = false;

};