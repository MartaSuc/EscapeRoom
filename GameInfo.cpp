// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInfo.h"
#include "Engine/Engine.h"

// Sets default values for this component's properties
UGameInfo::UGameInfo()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGameInfo::BeginPlay()
{
	Super::BeginPlay();
	FindTriggers();
	PrintStartMessage();

	CurrentRotation = GetOwner()->GetActorRotation();
	StopRotation = CurrentRotation;
}

void UGameInfo::FindTriggers()
{
	if (!StartInfoTrig) UE_LOG(LogTemp, Error, TEXT("%s has no StartInfoTrig set"), *GetOwner()->GetName());
	if (!EndGameTrig) UE_LOG(LogTemp, Error, TEXT("%s has no EndGameTrig set"), *GetOwner()->GetName());
}

float UGameInfo::MassOfActorsOnTrigger(ATriggerVolume* Trigger)
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

void UGameInfo::PrintStartMessage()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			1,        //write over previous message
			1.2f,   // Duration of message
			FColor::Cyan,   // Color
			FString::Printf(TEXT("WELCOME TO ESCAPE ROOM\n\nuse your MOUSE and ARROWS to move\n\npress RIGHT MOUSE BUTTON to grab object\nrelease to put it down\n\npress ESC to leave the game\n\nGood luck and hurry up!"))  // message
		);
	}
}

void UGameInfo::PrintEndGameMessage()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			1,        //write over previous message
			50.f,   // Duration of message
			FColor::Cyan,   // Color
			FString::Printf(TEXT("GOOD JOB FINDING THE EXIT\n\nYour time: %f\n\npress ESC to leave the game"), Time)  // message
		);
	}
}

void UGameInfo::Rotate(float DeltaTime)
{
	CurrentRotation = GetOwner()->GetActorRotation();
	StopRotation.Add(0.f, 359.f, 0.f);
	CubeRotation = FMath::Lerp(CurrentRotation, StopRotation, DeltaTime * 0.8f);
	GetOwner()->SetActorRotation(CubeRotation);
}

// Called every frame
void UGameInfo::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Rotate(DeltaTime);

	if (StartInfoTrig && MassOfActorsOnTrigger(StartInfoTrig) >= 50.f)
		PrintStartMessage();

	if (EndGameTrig && MassOfActorsOnTrigger(EndGameTrig) >= 50.f)
	{
		if (!bStopTime)
		{
			Time = GetWorld()->GetTimeSeconds();
			bStopTime = true;
		}
		PrintEndGameMessage();
	}
}
