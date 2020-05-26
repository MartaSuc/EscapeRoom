#include "Grabber.h"
#include "GameFramework/PlayerController.h"
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
	LineTraceEnd = PlayerViewPointLocation + PlayerReach *PlayerViewPointRotation.Vector();
}

void UGrabber::Grab()
{
	GetLocations();
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	if (HitResult.GetActor())
	{
		HitYaw = HitResult.GetActor()->GetActorRotation().Yaw;
		TargetRotation = { 0.f, HitYaw, 0.f };
		HitResult.GetActor()->SetActorRotation(TargetRotation);			//we want to pick objects that are set to straight position
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));			//debug line

	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

		HandlePhysics->GrabComponentAtLocationWithRotation( 
			ComponentToGrab,
			NAME_None,
			LineTraceEnd,
			TargetRotation);
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab released"));		 //debug line
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
	{
		HandlePhysics->SetTargetLocationAndRotation(LineTraceEnd, TargetRotation);
	}
}
