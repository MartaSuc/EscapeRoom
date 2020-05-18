// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandle();
	SetUpInputComponent();
}
void UGrabber::SetUpInputComponent()
{
	InputCompon = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputCompon) 
	{
		InputCompon->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
		InputCompon->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabber::Release);
	}
}
void UGrabber::FindPhysicsHandle()
{
	HandlePhysics = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (HandlePhysics == nullptr)  
		UE_LOG(LogTemp, Error, TEXT("No PhysicsHandle component found on: %s!"), *GetOwner()->GetName());
}
void UGrabber::GetLocations()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	LineTraceEnd = PlayerViewPointLocation + PlayerReach * PlayerViewPointRotation.Vector();
}
void UGrabber::Grab()
{
	GetLocations();
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed")); //debug line
	
	if (HitResult.GetActor())
		HandlePhysics->GrabComponentAtLocation(
			ComponentToGrab,
			NAME_None,
			LineTraceEnd);
}
void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab released")); //debug line
	if (HandlePhysics->GrabbedComponent)
		HandlePhysics->ReleaseComponent();
}
FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams);
//debug log
	if (Hit.GetActor())
		UE_LOG(LogTemp, Warning, TEXT("Actor hit: %s"), *Hit.GetActor()->GetName());

	return Hit;
}
// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	GetLocations();
	if (HandlePhysics->GrabbedComponent)
		HandlePhysics->SetTargetLocation(LineTraceEnd);

}
