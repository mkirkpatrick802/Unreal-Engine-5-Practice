 #pragma once

#include "CoreMinimal.h"
#include "Octree.h"

/// <summary>
/// An octree that holds 8 children, all of which are Octree's.
/// </summary>
class PROJECT_STINGER_API OctreeNode : public Octree
{
public:

    OctreeNode(const FVector& Center, float HalfWidth);
    OctreeNode(const FVector& Center, float HalfWidth, const TArray<Octree*>& Children);
    void Setup();

    virtual void Insert(AHornet* Hornet) override;
    virtual void Clear() override;

    virtual void GetNeighbors(TArray<AHornet*>& Neighbors, AHornet* Hornet) override;
    virtual TArray<AHornet*> GetHornets() override;
    virtual void Resize() override;

    virtual void DrawDebug(const UWorld* World) override;


private:

    FVector Center;
    float HalfWidth;
    TArray<Octree*> Children;

};