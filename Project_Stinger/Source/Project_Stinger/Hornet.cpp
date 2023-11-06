#include "Hornet.h"

AHornet::AHornet()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
	StaticMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SetRootComponent(StaticMesh);
}

void AHornet::BeginPlay()
{
	Super::BeginPlay();

	Transform = GetActorTransform();
}

void AHornet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateNeighbourhood();
	UpdateTransform();

	SetActorTransform(Transform);
}

void AHornet::UpdateNeighbourhood()
{

}

void AHornet::UpdateTransform()
{
	Transform.SetLocation(Transform.GetLocation() + 10);
}