#include "DoorOpenComponent.h"

// Sets default values for this component's properties
UDoorOpenComponent::UDoorOpenComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorOpenComponent::BeginPlay()
{
	Super::BeginPlay();

	float RotationAngle = 90.f;
	FRotator CurrentRotation = GetOwner()->GetActorRotation();

	FRotator NewRotation = FRotator{ CurrentRotation.Pitch, CurrentRotation.Yaw + RotationAngle, CurrentRotation .Roll};
	GetOwner()->SetActorRotation(NewRotation);
}


// Called every frame
void UDoorOpenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

