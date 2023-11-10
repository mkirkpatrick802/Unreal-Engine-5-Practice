#include "OctreeNode.h"

#include "Hornet.h"

OctreeNode::OctreeNode(const FVector& Center, float HalfWidth, const TArray<Octree*>& Children)
{
	this->Center = Center;
	this->Children = Children;
    this->HalfWidth = HalfWidth;
}

void OctreeNode::Insert(AHornet* Hornet)
{
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

	//Get the child that is absolutely holding the sphere
    int baseZone = 0;
    for (int i = 0; i < 3; i++)
    {
        if (Hornet->GetActorLocation()[i] > Center[i])
        {
            //Shifts the binary number to the left in respect to i:
            //the result will either be 1, 2, 4
            baseZone += (1 << i);
        }
    }

    //Add the sphere to the absolute child
    Children[baseZone]->Insert(Hornet);

    //Get how far away the sphere is from the center of the octree
    FVector difference = Hornet->GetActorLocation() - Center;

    //Check the difference with the sphere radius, if the radius is larger,
    //then the sphere is bleeding into another child
    int offset = 0; //Offset is used to hold which children are occupied
    for (int i = 0; i < 3; i++)
    {
        if (Hornet->GetColliderRadius() > FMath::Abs(difference[i]))
        {
            offset += (1 << i);
        }
    }

    //If offset is less then one, then no other children contain this sphere
    if (offset < 1) return;

    //Cycle through all remaining children and see if the radius is bleeding into them using the calculated offset
    for (int i = 0; i < 8; i++)
    {
        if (i == baseZone) continue;
        if (i > offset) continue;

        //Compares the bits of offset and i to see if i is contained in offset.
        //If it is then that means baseZone - i is occupied.
        //If offset is 7 then all children are occupied.
        //If offset is 6 then the 4th and 2nd children are occupied
        //If offset is 4 then only the 4th child is occupied.
        if (((offset & i) == i && i != 0) || (offset == 7 && i == 0))
        {
            Children[i]->Insert(Hornet);
        }
    }
}

void OctreeNode::Clear()
{
    for (int i = 0; i < 8; i++)
    {
        Children[i]->Clear();
    }
}

void OctreeNode::GetNeighbors(TArray<AHornet*>& Neighbors, AHornet* Hornet)
{
    for (int i = 0; i < 8; i++)
    {
        Children[i]->GetNeighbors(Neighbors, Hornet);
    }
}

void OctreeNode::DrawDebug(const UWorld* World)
{

    for (int i = 0; i < 8; i++)
    {
        Children[i]->DrawDebug(World);
    }

    // jesus fucking christ kill me now please
    // Calculate the center pole
    FVector CenterBottom = Center + FVector(0, 0, -HalfWidth);
    FVector CenterTop = Center + FVector(0, 0, HalfWidth);

    // Calculate the corner vertices of the cube
    FVector BottomLeftBack = Center + FVector(-HalfWidth, -HalfWidth, -HalfWidth);
    FVector BottomRightBack = Center + FVector(HalfWidth, -HalfWidth, -HalfWidth);
    FVector BottomRightFront = Center + FVector(HalfWidth, -HalfWidth, HalfWidth);
    FVector BottomLeftFront = Center + FVector(-HalfWidth, -HalfWidth, HalfWidth);

    FVector TopLeftBack = Center + FVector(-HalfWidth, HalfWidth, -HalfWidth);
    FVector TopRightBack = Center + FVector(HalfWidth, HalfWidth, -HalfWidth);
    FVector TopRightFront = Center + FVector(HalfWidth, HalfWidth, HalfWidth);
    FVector TopLeftFront = Center + FVector(-HalfWidth, HalfWidth, HalfWidth);

    // Calculate the middle plane
    FVector MiddleFront = Center + FVector(HalfWidth, 0, 0);
    FVector MiddleBack = Center + FVector(-HalfWidth, 0, 0);
    FVector MiddleLeft = Center + FVector(0, HalfWidth, 0);
    FVector MiddleRight = Center + FVector(0, -HalfWidth, 0);

    // Calculate the front plane
    FVector FrontTop = Center + FVector(HalfWidth, 0, HalfWidth);
    FVector FrontBottom = Center + FVector(HalfWidth, 0, -HalfWidth);
    FVector FrontLeft = Center + FVector(HalfWidth, HalfWidth, 0);
    FVector FrontRight = Center + FVector(HalfWidth, -HalfWidth, 0);

    // Calculate the back plane
    FVector BackTop = Center + FVector(-HalfWidth, 0, HalfWidth);
    FVector BackBottom = Center + FVector(-HalfWidth, 0, -HalfWidth);
    FVector BackLeft = Center + FVector(-HalfWidth, HalfWidth, 0);
    FVector BackRight = Center + FVector(-HalfWidth, -HalfWidth, 0);

    // Calculate the left plane
    FVector LeftTop = Center + FVector(0, HalfWidth, HalfWidth);
    FVector LeftBottom = Center + FVector(0, HalfWidth, -HalfWidth);

    // Calculate the right plane
    FVector RightTop = Center + FVector(0, -HalfWidth, HalfWidth);
    FVector RightBottom = Center + FVector(0, -HalfWidth, -HalfWidth);

    // DrawDebugLine center pole
    DrawDebugLine(World, CenterTop, CenterBottom, FColor::Red, false, -1, 0, 5.0f);

    // DrawDebugLine for the bottom face of the octree node
    DrawDebugLine(World, BottomLeftBack, BottomRightBack, FColor::Red, false, -1, 0, 5.0f);
    DrawDebugLine(World, BottomRightBack, BottomRightFront, FColor::Red, false, -1, 0, 5.0f);
    DrawDebugLine(World, BottomRightFront, BottomLeftFront, FColor::Red, false, -1, 0, 5.0f);
    DrawDebugLine(World, BottomLeftFront, BottomLeftBack, FColor::Red, false, -1, 0, 5.0f);

    // DrawDebugLine for the top face of the octree node
    DrawDebugLine(World, TopLeftBack, TopRightBack, FColor::Red, false, -1, 0, 5.0f);
    DrawDebugLine(World, TopRightBack, TopRightFront, FColor::Red, false, -1, 0, 5.0f);
    DrawDebugLine(World, TopRightFront, TopLeftFront, FColor::Red, false, -1, 0, 5.0f);
    DrawDebugLine(World, TopLeftFront, TopLeftBack, FColor::Red, false, -1, 0, 5.0f);

    // DrawDebugLine for the vertical edges connecting the top and bottom faces
    DrawDebugLine(World, BottomLeftBack, TopLeftBack, FColor::Red, false, -1, 0, 5.0f);
    DrawDebugLine(World, BottomRightBack, TopRightBack, FColor::Red, false, -1, 0, 5.0f);
    DrawDebugLine(World, BottomRightFront, TopRightFront, FColor::Red, false, -1, 0, 5.0f);
    DrawDebugLine(World, BottomLeftFront, TopLeftFront, FColor::Red, false, -1, 0, 5.0f);

    // DrawDebugLine for the middle edge of the octree node
    DrawDebugLine(World, Center, MiddleFront, FColor::Red, false, -1, 0, 5.0f);
    DrawDebugLine(World, Center, MiddleBack, FColor::Red, false, -1, 0, 5.0f);
    DrawDebugLine(World, Center, MiddleLeft, FColor::Red, false, -1, 0, 5.0f);
    DrawDebugLine(World, Center, MiddleRight, FColor::Red, false, -1, 0, 5.0f);

    // DrawDebugLine for the front plane
    DrawDebugLine(World, FrontTop, FrontBottom, FColor::Red, false, -1, 0, 5.0f);
    DrawDebugLine(World, FrontLeft, FrontRight, FColor::Red, false, -1, 0, 5.0f);

    // DrawDebugLine for the back plane
    DrawDebugLine(World, BackTop, BackBottom, FColor::Red, false, -1, 0, 5.0f);
    DrawDebugLine(World, BackLeft, BackRight, FColor::Red, false, -1, 0, 5.0f);

    // DrawDebugLine for the left plane
    DrawDebugLine(World, LeftTop, LeftBottom, FColor::Red, false, -1, 0, 5.0f);
    DrawDebugLine(World, FrontLeft, BackLeft, FColor::Red, false, -1, 0, 5.0f);

    // DrawDebugLine for the right plane
    DrawDebugLine(World, RightTop, RightBottom, FColor::Red, false, -1, 0, 5.0f);
    DrawDebugLine(World, FrontRight, BackRight, FColor::Red, false, -1, 0, 5.0f);

    // DrawDebugLine for the top plane
    DrawDebugLine(World, FrontTop, BackTop, FColor::Red, false, -1, 0, 5.0f);
    DrawDebugLine(World, LeftTop, RightTop, FColor::Red, false, -1, 0, 5.0f);

    // DrawDebugLine for the bottom plane
    DrawDebugLine(World, FrontBottom, BackBottom, FColor::Red, false, -1, 0, 5.0f);
    DrawDebugLine(World, LeftBottom, RightBottom, FColor::Red, false, -1, 0, 5.0f);
}