// /*/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GrabberComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BE_API UGrabberComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabberComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(EditAnywhere)
	float Reach = 100.f;

	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandleComp { nullptr };
	UPROPERTY()
	UInputComponent* InputComp{ nullptr };

	void GrabPressed();
	void GrabReleased();
	void FindPhysicsHandle();
	void SetupInputComponent();
	FHitResult GetFirstPhysicsBodyInReach() const;
	FVector GetLineTraceEnd() const;
	FVector GetPlayersWorldPosition() const;
};
