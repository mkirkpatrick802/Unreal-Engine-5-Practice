#include "Octree.h"

#include "OctreeLeaf.h"
#include "OctreeNode.h"

Octree* Octree::Create(const FVector& Center, float HalfWidth, int Depth)
{
    if(BoundsMin == FVector::ZeroVector || BoundsMax == FVector::ZeroVector)
    {
        BoundsMin = FVector(Center.X - HalfWidth, Center.Y - HalfWidth, Center.Z - HalfWidth);
        BoundsMax = FVector(Center.X + HalfWidth, Center.Y + HalfWidth, Center.Z + HalfWidth);
    }

    if (Depth == 0)
    {
        return new OctreeLeaf(Center);
    }
    else
    {
        HalfWidth /= 2;
        TArray<Octree*> Children;
        Children.SetNum(8);

        /*
         *
         * Bits count right to left
         *
         * First bit represents the X axis
         * Second bit represents the Y axis
         * Third bit represents the Z axis
         *
         * 0 = 000
         * 1 = 001
         * 2 = 010
         * 3 = 011
         * 4 = 100
         * 5 = 101
         * 6 = 110
         * 7 = 111
         *
        */

        for (int i = 0; i < 8; i++)
        {
            FVector Offset = Center;

            //Move offset up on X axis if it has the first bit assigned, down if not
            Offset += FVector(1, 0, 0) * ((i & 1) != 0 ? HalfWidth : -HalfWidth);

            //Move offset up on Y axis if it has the second bit assigned, down if not
            Offset += FVector(0, 1, 0) * ((i & 2) != 0 ? HalfWidth : -HalfWidth);

            //Move offset up on the Z axis if it has the third bit assigned, down if not
            Offset += FVector(0, 0, 1) * ((i & 4) != 0 ? HalfWidth : -HalfWidth);

            //Add Child to List
            Children[i] = Create(Offset, HalfWidth, Depth - 1);
        }

        OctreeNode* Node = new OctreeNode(Center, HalfWidth * 2, Children);
        if(!RootSet)
        {
            Node->Type = Root;
            RootSet = true;
        }

        return Node;
    }
}

void Octree::GetBounds(FVector& Min, FVector& Max)
{
    Min = BoundsMin;
    Max = BoundsMax;
}
