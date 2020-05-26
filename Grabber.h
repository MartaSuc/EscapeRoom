#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ESCAPEROOM_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabber();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void GetLocations();
	void Grab();
	void Release();
	void FindPhysicsHandle();
	void SetUpInputComponent();
	FHitResult GetFirstPhysicsBodyInReach() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float PlayerReach = 250.f;
	float HitYaw= 0.f;
	FRotator PlayerViewPointRotation = { 0.f, 0.f, 0.f };
	FVector PlayerViewPointLocation = { 0.f, 0.f, 0.f };
	FVector LineTraceEnd = { 0.f, 0.f, 0.f };
	FRotator TargetRotation = { 0.f, 0.f, 0.f };

	UPROPERTY()
	UPhysicsHandleComponent* HandlePhysics = nullptr;
	UPROPERTY()
	UInputComponent* InputCompon = nullptr;
};
