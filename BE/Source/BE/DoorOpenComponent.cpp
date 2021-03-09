#include "DoorOpenComponent.h"

// Sets default values for this component's properties
UDoorOpenComponent::UDoorOpenComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UDoorOpenComponent::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	TargetYaw = InitialYaw + DeltaYaw;	
}


// Called every frame
void UDoorOpenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	CurrentRotation.Yaw = FMath::FInterpConstantTo(CurrentRotation.Yaw, TargetYaw, DeltaTime, 40);
	
	GetOwner()->SetActorRotation(CurrentRotation);

	UE_LOG(LogTemp, Warning, TEXT("Current Yaw is %f"), CurrentRotation.Yaw);
	// ...
}

