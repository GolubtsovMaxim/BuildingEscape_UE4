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

	FindPhysicsHandle();
	SetupInputComponent();
	
}

void UGrabberComponent::GrabPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab is pressed"));
	FHitResult HitResult = GetFirstPhysicsBodyInReach();

	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

	if (HitResult.GetActor())
	{
		PhysicsHandleComp->GrabComponentAtLocation
		(
			ComponentToGrab,
			NAME_None,
			GetLineTraceEnd()
		);
	}
	
}

void UGrabberComponent::GrabReleased()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab is released"));
	PhysicsHandleComp->ReleaseComponent();
}

void UGrabberComponent::FindPhysicsHandle()
{
	PhysicsHandleComp = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandleComp)
	{
		UE_LOG(LogTemp, Error, TEXT("%s doesn't have a PhysicsHandleComp or it's null"), *GetOwner()->GetName());
	}
	else
	{
		
	}
}

void UGrabberComponent::SetupInputComponent()
{
	InputComp = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("InputComponent for %s found"), *GetOwner()->GetName());
		InputComp->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabberComponent::GrabPressed);
		InputComp->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabberComponent::GrabReleased);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s doesn't have an InputComponent or it's null"), *GetOwner()->GetName());
	}
}


void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandleComp->GrabbedComponent)
	{
		PhysicsHandleComp->SetTargetLocation(GetLineTraceEnd());
	}
}

FHitResult UGrabberComponent::GetFirstPhysicsBodyInReach() const
{
	FHitResult HitResult;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		GetPlayersWorldPosition(),
		GetLineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	if (HitResult.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is hit"), *HitResult.GetActor()->GetName());
	}

	return HitResult;
}

FVector UGrabberComponent::GetPlayersWorldPosition() const
{
	FVector ViewVector;
	FRotator ViewRotator;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(ViewVector,
		ViewRotator);

	//UE_LOG(LogTemp, Warning, TEXT("Player's ViewVector is %s. \n ViewRotator is %s"), *ViewVector.ToString(), *ViewRotator.ToString())

	return ViewVector;
}

FVector UGrabberComponent::GetLineTraceEnd() const
{
	FVector ViewVector;
	FRotator ViewRotator;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(ViewVector,
		ViewRotator);

	return ViewVector + ViewRotator.Vector() * Reach;
}
