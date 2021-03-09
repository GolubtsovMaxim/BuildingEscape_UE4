// /*/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float TargetYaw;

	UPROPERTY(EditAnywhere)
	float DeltaYaw;

	float InitialYaw;
};
