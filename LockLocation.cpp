// Fill out your copyright notice in the Description page of Project Settings.


#include "LockLocation.h"

// Sets default values for this component's properties
ULockLocation::ULockLocation()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULockLocation::BeginPlay()
{
	Super::BeginPlay();
	FindTrigger();
}


void ULockLocation::FindTrigger()
{
	if (!DoorTrig) UE_LOG(LogTemp, Error, TEXT("%s has no DoorTrig set"), *GetOwner()->GetName());
}

float ULockLocation::MassOfActorsOnTrigger(ATriggerVolume* Trigger)
{
	float TotalMass = 0.0f;
	TArray <AActor*> ActorsOverlaping;
	if (!Trigger) return TotalMass;
	Trigger->GetOverlappingActors(OUT ActorsOverlaping);

	for (AActor* Actor : ActorsOverlaping)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}

// Called every frame
void ULockLocation::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (DoorTrig && MassOfActorsOnTrigger(DoorTrig) >= 60.f)	
	{
		if (!bLock)
		{
			bLock = true;
			CurrentLocation = GetOwner()->GetActorLocation();
			CurrentRotation = GetOwner()->GetActorRotation();
		}
	}

	if (bLock)
	{
		GetOwner()->SetActorLocation(CurrentLocation);
		GetOwner()->SetActorRotation(CurrentRotation);
	}
}
