#include "OctreeNode.h"

#include "Hornet.h"
#include "OctreeLeaf.h"

OctreeNode::OctreeNode(const FVector& Center, float HalfWidth)
{
    Type = Node;
    this->Center = Center;
    this->HalfWidth = HalfWidth;
    Children.SetNum(8);

    const float Temp = HalfWidth / 2;
;   for (int i = 0; i < 8; i++)
    {
        FVector Offset = Center;

        //Move offset up on X axis if it has the first bit assigned, down if not
        Offset += FVector(1, 0, 0) * ((i & 1) != 0 ? Temp : -Temp);

        //Move offset up on Y axis if it has the second bit assigned, down if not
        Offset += FVector(0, 1, 0) * ((i & 2) != 0 ? Temp : -Temp);

        //Move offset up on the Z axis if it has the third bit assigned, down if not
        Offset += FVector(0, 0, 1) * ((i & 4) != 0 ? Temp : -Temp);

        //Add Child to List
        Children[i] = new OctreeLeaf(Offset);
    }

	Setup();
}

OctreeNode::OctreeNode(const FVector& Center, float HalfWidth, const TArray<Octree*>& Children)
{
    Type = Node;
	this->Center = Center;
    this->HalfWidth = HalfWidth;
	this->Children = Children;

    Setup();
}

void OctreeNode::Setup()
{
    if(Type == Root)
    {
        CurrentDepth = 1;
        for (int i = 0; i < 8; i++)
        {
            Children[i]->SetDepth(CurrentDepth);
        }
    }
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

    // HornetsLocation
    FVector HornetLocation = Hornet->GetActorLocation();

	// Get the child that is absolutely holding the sphere
    int BaseZone = 0;
    for (int i = 0; i < 3; i++)
    {
        if (HornetLocation[i] > Center[i])
        {
            // Shifts the binary number to the left in respect to i:
            // the result will either be 1, 2, 4
            BaseZone += (1 << i);
        }
    }

    // Add the sphere to the absolute child
    Children[BaseZone]->Insert(Hornet);

    // Get how far away the sphere is from the center of the octree
    const FVector Difference = HornetLocation - Center;

    // Check the difference with the sphere radius, if the radius is larger,
    // then the sphere is bleeding into another child
    // Offset is used to hold which children are occupied
	int AxisOffset = 0;
    for (int i = 0; i < 3; i++)
    {
        if (Hornet->GetColliderRadius() > FMath::Abs(Difference[i]))
            AxisOffset += (1 << i);
    }

    // If offset is less then one, then no other children contain this sphere
    if (AxisOffset > 0)
    {
        // Use the offset to determine what children the sphere is overlapping into
		// This only accounts for 3 possible overlaps (the x, y and z axis)
        for (int i = 0; i < 3; i++)
        {
            if ((AxisOffset & 1 << i) != 0)
                Children[BaseZone ^ 1 << i]->Insert(Hornet);
        }

        // Calculate diagonal overlaps
        if ((AxisOffset & 1) != 0 && (AxisOffset & 2) != 0)
        {
            Children[BaseZone ^ 3]->Insert(Hornet);
        }

        if ((AxisOffset & 1) != 0 && (AxisOffset & 4) != 0)
        {
            Children[BaseZone ^ 5]->Insert(Hornet);
        }

        if ((AxisOffset & 2) != 0 && (AxisOffset & 4) != 0)
        {
            Children[BaseZone ^ 6]->Insert(Hornet);
        }

        if ((AxisOffset & 1) != 0 && (AxisOffset & 2) != 0 && (AxisOffset & 4) != 0)
        {
            Children[BaseZone ^ 7]->Insert(Hornet);
        }
    }
}


void OctreeNode::Resize()
{
    for(int i = 0; i < 8; i++)
    {
        if (Children[i]->GetHornets().Num() > RESIZE_THRESHOLD)
        {
            if (CurrentDepth + 1 > MAX_DEPTH) continue;

        	Octree* Child = Children[i];
            if (Child->Type != Leaf) continue;

            TArray<AHornet*> HornetsToMove;
        	{
                OctreeLeaf* TempLeaf = static_cast<OctreeLeaf*>(Child);
                HornetsToMove = TempLeaf->GetHornets();
        	}

        	const float Temp = HalfWidth / 2;
        	FVector Offset = Center;

        	//Move offset up on X axis if it has the first bit assigned, down if not
        	Offset += FVector(1, 0, 0) * ((i & 1) != 0 ? Temp : -Temp);

        	//Move offset up on Y axis if it has the second bit assigned, down if not
        	Offset += FVector(0, 1, 0) * ((i & 2) != 0 ? Temp : -Temp);

        	//Move offset up on the Z axis if it has the third bit assigned, down if not
        	Offset += FVector(0, 0, 1) * ((i & 4) != 0 ? Temp : -Temp);

        	Children[i] = new OctreeNode(Offset, Temp);
            Children[i]->SetDepth(CurrentDepth);

	        for (const auto ToMove : HornetsToMove)
	        {
                Children[i]->Insert(ToMove);
	        }

            delete Child;
            continue;
        }

    	if (Children[i]->GetHornets().Num() < RESIZE_THRESHOLD && Children[i]->GetHornets().Num() != 0)
        {
            Octree* Child = Children[i];

            if (Child->Type != Node) continue;

            const float Temp = HalfWidth / 2;
            FVector Offset = Center;

            //Move offset up on X axis if it has the first bit assigned, down if not
            Offset += FVector(1, 0, 0) * ((i & 1) != 0 ? Temp : -Temp);

            //Move offset up on Y axis if it has the second bit assigned, down if not
            Offset += FVector(0, 1, 0) * ((i & 2) != 0 ? Temp : -Temp);

            //Move offset up on the Z axis if it has the third bit assigned, down if not
            Offset += FVector(0, 0, 1) * ((i & 4) != 0 ? Temp : -Temp);

            Children[i] = new OctreeLeaf(Offset);

            delete Child;
        }
    }

    for (int i = 0; i < 8; i++)
    {
        Children[i]->Resize();
    }
}


TArray<AHornet*> OctreeNode::GetHornets()
{
    TArray<AHornet*> UniqueHornets;

    for (int i = 0; i < 8; i++)
    {
	    for (auto Hornet : Children[i]->GetHornets())
	    {
            UniqueHornets.AddUnique(Hornet);
	    }
    }

    return UniqueHornets;
}

void OctreeNode::Clear()
{
    for (int i = 0; i < 8; i++)
    {
        Children[i]->Clear();
    }
}

// This is the same code as I used for the insert and i believe that it is working well
// Hopefully it stays that way
void OctreeNode::GetNeighbors(TArray<AHornet*>& Neighbors, AHornet* Hornet)
{
    FVector HornetLocation = Hornet->GetActorLocation();

    int BaseZone = 0;
    for (int i = 0; i < 3; i++)
    {
        if (HornetLocation[i] > Center[i])
        {
            BaseZone += (1 << i);
        }
    }

    Children[BaseZone]->GetNeighbors(Neighbors, Hornet);

    const FVector Difference = HornetLocation - Center;

    int AxisOffset = 0;
    for (int i = 0; i < 3; i++)
    {
        if (Hornet->GetVisionRadius() > FMath::Abs(Difference[i]))
            AxisOffset += (1 << i);
    }

    if (AxisOffset > 0)
    {
        for (int i = 0; i < 3; i++)
        {
            if ((AxisOffset & 1 << i) != 0)
                Children[BaseZone ^ 1 << i]->GetNeighbors(Neighbors, Hornet);
        }

        if ((AxisOffset & 1) != 0 && (AxisOffset & 2) != 0)
        {
            Children[BaseZone ^ 3]->GetNeighbors(Neighbors, Hornet);
        }

        if ((AxisOffset & 1) != 0 && (AxisOffset & 4) != 0)
        {
            Children[BaseZone ^ 5]->GetNeighbors(Neighbors, Hornet);
        }

        if ((AxisOffset & 2) != 0 && (AxisOffset & 4) != 0)
        {
            Children[BaseZone ^ 6]->GetNeighbors(Neighbors, Hornet);
        }

        if ((AxisOffset & 1) != 0 && (AxisOffset & 2) != 0 && (AxisOffset & 4) != 0)
        {
            Children[BaseZone ^ 7]->GetNeighbors(Neighbors, Hornet);
        }
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
