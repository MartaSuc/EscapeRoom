// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabber();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	float PlayerReach = 100.f;
	FRotator PlayerViewPointRotation = { 0.f, 0.f, 0.f };
	FVector PlayerViewPointLocation = { 0.f, 0.f, 0.f };
	FVector LineTraceEnd = { 0.f, 0.f, 0.f };

	UPhysicsHandleComponent* HandlePhysics = nullptr;
	UInputComponent* InputCompon = nullptr;

	void GetLocations();
	void Grab();
	void Release();
	void FindPhysicsHandle();
	void SetUpInputComponent();
	FHitResult GetFirstPhysicsBodyInReach() const;
};
