#include "OctreeLeaf.h"

#include "Hornet.h"

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
	if(Hornets.IsEmpty()) return;
	if(!Hornets.Contains(Hornet)) return;

	FVector HornetLoc = Hornet->GetActorLocation();
	for (auto Child : Hornets)
	{
		if(Child == Hornet) continue;

		FVector ChildLoc = Child->GetActorLocation();
		FVector Difference = ChildLoc - HornetLoc;
		if(Difference.Length() - Child->GetColliderRadius() < Hornet->GetVisionRadius())
		{
			Neighbors.AddUnique(Child);
		}
	}
}

void OctreeLeaf::DrawDebug(const UWorld* World)
{
	if(Hornets.IsEmpty()) return;

	DrawDebugSphere(World, Center, 200, 20, FColor::Blue, false, -1, 0, 5);
}