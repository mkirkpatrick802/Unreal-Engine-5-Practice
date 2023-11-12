#include "Hornet.h"

#include "Octree.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"

AHornet::AHornet()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(FName("Sphere Collider"));
	SphereCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SphereCollider->SetSphereRadius(ColliderRadius);
	SetRootComponent(SphereCollider);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Mesh"));
	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	Arrow = CreateDefaultSubobject<UArrowComponent>(FName("Forward Arrow"));
	Arrow->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Arrow->ArrowSize = 1.5;
	Arrow->ArrowLength = 100;
}

void AHornet::BeginPlay()
{
	Super::BeginPlay();

	Transform = GetActorTransform();
	Velocity = FVector(1,0,1);
}

void AHornet::SetTree(Octree* Tree)
{
	HornetOctree = Tree;
}

void AHornet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Movement
	UpdateNeighbourhood();
	UpdateTransform();

	// Debug
	HornetOctree->DrawDebug(GetWorld());
	DrawDebug();
}

void AHornet::UpdateNeighbourhood()
{
	Neighborhood.Empty();
	HornetOctree->GetNeighbors(Neighborhood, this);
}

void AHornet::UpdateTransform()
{
	Transform.SetLocation(Transform.GetLocation() + Velocity);
	Transform.SetRotation(Velocity.ToOrientationQuat());
	//SetActorTransform(Transform);
}

void AHornet::DrawDebug() const
{
	const UWorld* World = GetWorld();
	const FVector& Location = GetActorLocation();

	// Movement Vector
	DrawDebugLine(World, Location,Location + Velocity * 100.0f, FColor::Green, false, -1, 0, 1.0f);

	// Vision Radius
	DrawDebugSphere(World, GetActorLocation(), VisionRadius, 20, FColor::Blue, false, -1, 0, .2f);

	//Draw Connections to Neighbors
	for (const auto Hornet : Neighborhood)
	{
		DrawDebugLine(World, Location, Hornet->GetActorLocation(), FColor::Yellow, false, -1, 0, 3);
	}
}
