#include "DoorOpenComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

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

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has the DoorOpenComponent, but no PressurePlate set"), *GetOwner()->GetName())
	}

	IncomingActor = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UDoorOpenComponent::OpenDoor(float DeltaTime)
{
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	//CurrentRotation.Yaw = FMath::FInterpConstantTo(CurrentRotation.Yaw, TargetYaw, DeltaTime, 40);
	CurrentRotation.Yaw = FMath::Lerp(CurrentRotation.Yaw, TargetYaw, DeltaTime * DoorOpenSpeed);

	GetOwner()->SetActorRotation(CurrentRotation);
}

void UDoorOpenComponent::CloseDoor(float DeltaTime)
{
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	//CurrentRotation.Yaw = FMath::FInterpConstantTo(CurrentRotation.Yaw, TargetYaw, DeltaTime, 40);
	CurrentRotation.Yaw = FMath::Lerp(CurrentRotation.Yaw, InitialYaw, DeltaTime * DoorCloseSpeed);

	GetOwner()->SetActorRotation(CurrentRotation);
}


void UDoorOpenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && IncomingActor && PressurePlate->IsOverlappingActor(IncomingActor))
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
}

