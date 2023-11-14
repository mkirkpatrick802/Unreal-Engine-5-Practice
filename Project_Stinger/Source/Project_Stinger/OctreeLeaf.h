#pragma once

#include "CoreMinimal.h"
#include "Octree.h"

/// <summary>
/// An octree that holds only hornets.
/// </summary>
class PROJECT_STINGER_API OctreeLeaf : public Octree
{
public:

    OctreeLeaf();
    OctreeLeaf(const FVector& New);
    void SetCenter(const FVector& New) { Center = New; }
    virtual void Insert(AHornet* Hornet) override;
    virtual void Clear() override;

    virtual void GetNeighbors(TArray<AHornet*>& Neighbors, AHornet* Hornet) override;
    virtual TArray<AHornet*> GetHornets() override;
    virtual void Resize() override;

    virtual void DrawDebug(const UWorld* World) override;

private:

	FVector Center;
    TArray<AHornet*> Hornets;

};
