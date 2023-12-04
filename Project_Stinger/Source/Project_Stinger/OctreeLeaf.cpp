#include "OctreeLeaf.h"

#include "Hornet.h"

OctreeLeaf::OctreeLeaf()
{
	Type = Leaf;
}

OctreeLeaf::OctreeLeaf(const FVector& New)
{
	Type = Leaf;
	Center = New;
}

void OctreeLeaf::Insert(AHornet* Hornet)
{
	Hornets.Add(Hornet);
}

void OctreeLeaf::Clear()
{
	Hornets.Empty();
}

// TODO: Check if hornet vision radius reaches this leaf, if it does find neighbors, if it does not return
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

TArray<AHornet*> OctreeLeaf::GetHornets()
{
	return Hornets;
}

void OctreeLeaf::DrawDebug(const UWorld* World)
{
	if(Hornets.IsEmpty()) return;

	DrawDebugSphere(World, Center, 200, 20, FColor::Blue, false, -1, 0, 5);
}

void OctreeLeaf::Resize()
{

}