#pragma once

#include "CoreMinimal.h"
#include "Octree.h"

/// <summary>
/// An octree that holds only hornets.
/// </summary>
class PROJECT_STINGER_API OctreeLeaf : public Octree
{
public:

    void SetCenter(const FVector& New) { Center = New; }
    virtual void Insert(AHornet* Hornet) override;
    virtual void Clear() override;
    virtual void GetNeighbors(TArray<AHornet*>& Neighbors, AHornet* Hornet) override;
    virtual void DrawDebug(const UWorld* World) override;

private:

	FVector Center;
    TArray<AHornet*> Hornets;

};
