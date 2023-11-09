#include "Hornet.h"

#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"

AHornet::AHornet()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(FName("Sphere Collider"));
	SphereComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SetRootComponent(SphereComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
	StaticMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	/*Arrow = CreateDefaultSubobject<UArrowComponent>(FName("Forward Arrow"));
	Arrow->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Arrow->ArrowSize = 1.5;
	Arrow->ArrowLength = 100;*/
}

void AHornet::BeginPlay()
{
	Super::BeginPlay();

	Transform = GetActorTransform();
	Velocity = FVector(1,1,1);
}

void AHornet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateNeighbourhood();
	UpdateTransform();

	DrawDebug();
}

void AHornet::UpdateNeighbourhood()
{

}

void AHornet::UpdateTransform()
{
	Transform.SetLocation(Transform.GetLocation() + Velocity);
	Transform.SetRotation(Velocity.ToOrientationQuat());
	SetActorTransform(Transform);
}

void AHornet::DrawDebug() const
{
	const UWorld* World = GetWorld();
	const FVector& Location = Transform.GetLocation();
	DrawDebugLine(World, Location,Location + Velocity * 100.0f, FColor::Green, false, -1, 0, 1.0f);
}
