// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	CurrentRotation = GetOwner()->GetActorRotation();
	OpenRotation = CloseRotation = CurrentRotation;
	OpenRotation.Add(0, Target, 0);
	//CloseRotation.Add(0, -Target, 0);
	

	if (!PressurePlate) UE_LOG(LogTemp, Error, TEXT("%s has no PressurePlate set"), *GetOwner()->GetName());

	OneThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && PressurePlate->IsOverlappingActor(OneThatOpens))
	{
		OpeningDoor(DeltaTime);

		LastDoorOpened = GetWorld()->GetTimeSeconds();
	}
	if (PressurePlate && !PressurePlate->IsOverlappingActor(OneThatOpens))
	{
		if (GetWorld()->GetTimeSeconds() - LastDoorOpened > CloseDoorDelay) ClosingDoor(DeltaTime);
	}
}

void UOpenDoor::OpeningDoor(float DeltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("Yaw: %f"), GetOwner() -> GetActorRotation().Yaw);
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	CurrentRotation = GetOwner()->GetActorRotation();
	Door = FMath::Lerp(CurrentRotation, OpenRotation, DeltaTime * 0.6f);
	GetOwner()->SetActorRotation(Door);
}	

void UOpenDoor::ClosingDoor(float DeltaTime)
{
	CurrentRotation = GetOwner()->GetActorRotation();
	Door = FMath::Lerp(CurrentRotation, CloseRotation, DeltaTime * 1.9f);
	GetOwner()->SetActorRotation(Door);
}
