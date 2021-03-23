#include "GrabberComponent.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabberComponent::UGrabberComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UGrabberComponent::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber Component has been initialized for object %s, of class %s"),
		   *this->GetOwner()->GetName(), *this->GetOwner()->GetClass()->GetName());

	PhysicsHandleComp = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandleComp)
	{
		UE_LOG(LogTemp, Error, TEXT("%s doesn't have a PhysicsHandleComp or it's null"), *GetOwner()->GetName());
	}

	InputComp = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!InputComp)
	{
		UE_LOG(LogTemp, Error, TEXT("%s doesn't have an InputComponent or it's null"), *GetOwner()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("InputComponent for %s found"), *GetOwner()->GetName());
		InputComp->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabberComponent::GrabPressed);
		InputComp->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabberComponent::GrabReleased);
	}
}

void UGrabberComponent::GrabPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab is pressed"));
}

void UGrabberComponent::GrabReleased()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab is released"));
}



// Called every frame
void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector ViewVector;
	FRotator ViewRotator;
	
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(ViewVector,
	 ViewRotator);

	//UE_LOG(LogTemp, Warning, TEXT("Player's ViewVector is %s. \n ViewRotator is %s"), *ViewVector.ToString(), *ViewRotator.ToString())

	FVector LineTraceEnd = ViewVector + ViewRotator.Vector() * Reach;

	DrawDebugLine(GetWorld(),
		ViewVector,
		LineTraceEnd,
		FColor::Orange,
		false,
		0.f, 
		0,
		5.f
		);

	FHitResult HitResult;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	
	GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		ViewVector,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
		);

	if (HitResult.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is hit"), *HitResult.GetActor()->GetName());
	}
}

