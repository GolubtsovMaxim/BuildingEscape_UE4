// /*/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "DoorOpenComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BE_API UDoorOpenComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpenComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void OpenDoor(float DeltaTime);

	virtual void CloseDoor(float DeltaTime);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float TargetYaw;

	float InitialYaw;

	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnywhere)
	AActor* IncomingActor;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
	float DeltaYaw;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay;

	UPROPERTY(EditAnywhere)
	float DoorCloseSpeed = 1.f;

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = 1.f;
};
