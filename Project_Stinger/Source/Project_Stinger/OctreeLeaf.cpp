#include "OctreeLeaf.h"

void OctreeLeaf::Insert(AHornet* Hornet)
{
	Hornets.Add(Hornet);
}

void OctreeLeaf::Clear()
{
	Hornets.Empty();
}

void OctreeLeaf::GetNeighbors(TArray<AHornet*>& Neighbors, AHornet* Hornet)
{

}

void OctreeLeaf::DrawDebug(const UWorld* World)
{
	if(Hornets.Num() > 0)
		DrawDebugSphere(World, Center, 50, 10, FColor::Blue, false, -1, 0, 5);
}