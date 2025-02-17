// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();
	const FString ObjectPos = GetOwner()->GetActorLocation().ToString();
	UE_LOG
		(LogTemp, Warning, TEXT("World Position Component has been initialized for object %s, of class %s, is at position %s"), 
		*this->GetOwner()->GetName(),  *this->GetOwner()->GetClass()->GetName(),
		*ObjectPos);	
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

