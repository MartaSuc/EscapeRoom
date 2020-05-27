// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

#define OUT

// Sets default values for this component's properties
UDoor::UDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UDoor::BeginPlay()
{
	Super::BeginPlay();
	
	FindTriggers();

	CurrentLocation = GetOwner()->GetActorLocation();
	OpenLocation = CloseLocation = CurrentLocation;
	OpenLocation += {TargetX, TargetY, .0f};

	OpeningDoor(2.f);			//delta time set to 1.f
}

void UDoor::FindTriggers()
{
	if (!GeneratorTrig) UE_LOG(LogTemp, Error, TEXT("%s has no GeneratorTrig set"), *GetOwner()->GetName());
	if (!DoorTrig) UE_LOG(LogTemp, Error, TEXT("%s has no GlassDoorTrig set"), *GetOwner()->GetName());
	if (!TrapRoomTrig1) UE_LOG(LogTemp, Error, TEXT("%s has no TrapRoomTrig1 set"), *GetOwner()->GetName());
	if (!TrapRoomTrig2) UE_LOG(LogTemp, Error, TEXT("%s has no TrapRoomTrig2 set"), *GetOwner()->GetName());
	if (!TrapRoomTrig3) UE_LOG(LogTemp, Error, TEXT("%s has no TrapRoomTrig3 set"), *GetOwner()->GetName());
	if (!TrapRoomTrig4) UE_LOG(LogTemp, Error, TEXT("%s has no TrapRoomTrig4 set"), *GetOwner()->GetName());
	if (!BottlesPlatformTrig) UE_LOG(LogTemp, Error, TEXT("%s has no BottlesPlatformTrig set"), *GetOwner()->GetName());
}

void UDoor::OpeningDoor(float DeltaTime)
{
	CurrentLocation = GetOwner()->GetActorLocation();
	Door = FMath::Lerp(CurrentLocation, OpenLocation, DeltaTime * 0.6f);
	GetOwner()->SetActorLocation(Door);
}

void UDoor::ClosingDoor()
{
	GetOwner()->SetActorLocation(CloseLocation);
}

void UDoor::BottlePlatformTrigAppear()
{
	if (BottlesPlatformTrig)
		BottlesPlatformTrig->SetActorLocation(FVector(-495.0f, -920.0f, 255.0f));		//hard-coding location of BottlePlatformTrigger
	bGeneratorTrigNotUsed = false;													//setting bool to false to make sure GeneratorTrig can be used only once
}

void UDoor::DoorTrigAppear()
{
	if (DoorTrig)
		DoorTrig->SetActorLocation(FVector(510.0f, -1275.0f, 250.0f));	//hard-coding location of DoorTrigger
}

float UDoor::MassOfActorsOnTrigger(ATriggerVolume* Trigger)
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
void UDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//GeneratorTrigger
	if (GeneratorTrig && bGeneratorTrigNotUsed && MassOfActorsOnTrigger(GeneratorTrig) >= 600.f)	//one generator's weight is set to 300kg
	{
		ClosingDoor();
		DoorTrigAppear();
	}

	//GlassDoorTrigger
	if (DoorTrig && MassOfActorsOnTrigger(DoorTrig) >= 50.f)		//pawn's (player's) weight is set to 60kg
	{
		OpeningDoor(DeltaTime);
		BottlePlatformTrigAppear();
	}

	//TrapRoomTriggers
	if (!bGeneratorTrigNotUsed)
	{
		if (TrapRoomTrig1 && MassOfActorsOnTrigger(TrapRoomTrig1) >= 1.f &&
			TrapRoomTrig2 && MassOfActorsOnTrigger(TrapRoomTrig2) >= 1.f &&
			TrapRoomTrig3 && MassOfActorsOnTrigger(TrapRoomTrig3) >= 1.f &&
			TrapRoomTrig4 && MassOfActorsOnTrigger(TrapRoomTrig4) >= 1.f)
			OpeningDoor(DeltaTime);
		else
			ClosingDoor();
	}
}
