#include "GlassDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

#define OUT

// Sets default values for this component's properties
UGlassDoor::UGlassDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGlassDoor::BeginPlay()
{
	Super::BeginPlay();
	FindTriggers();

	CurrentRotation = GetOwner()->GetActorRotation();
	OpenRotation = CloseRotation = CurrentRotation;
	CloseRotation.Add(.0f, Target, .0f);	
}

void UGlassDoor::FindTriggers()
{
	if (!GeneratorTrig) UE_LOG(LogTemp, Error, TEXT("%s has no GeneratorTrig set"), *GetOwner()->GetName());
	if (!GlassDoorTrig) UE_LOG(LogTemp, Error, TEXT("%s has no GlassDoorTrig set"), *GetOwner()->GetName());
	if (!TrapRoomTrig1) UE_LOG(LogTemp, Error, TEXT("%s has no TrapRoomTrig1 set"), *GetOwner()->GetName());
	if (!TrapRoomTrig2) UE_LOG(LogTemp, Error, TEXT("%s has no TrapRoomTrig2 set"), *GetOwner()->GetName());
	if (!TrapRoomTrig3) UE_LOG(LogTemp, Error, TEXT("%s has no TrapRoomTrig3 set"), *GetOwner()->GetName());
	if (!TrapRoomTrig4) UE_LOG(LogTemp, Error, TEXT("%s has no TrapRoomTrig4 set"), *GetOwner()->GetName());
	if (!BottlesPlatformTrig) UE_LOG(LogTemp, Error, TEXT("%s has no BottlesPlatformTrig set"), *GetOwner()->GetName());
}

void UGlassDoor::OpeningDoor(float DeltaTime)
{
	CurrentRotation = GetOwner()->GetActorRotation();
	Door = FMath::Lerp(CurrentRotation, OpenRotation, DeltaTime * 0.6f);
	GetOwner()->SetActorRotation(Door);	
}

void UGlassDoor::ClosingDoor()
{
	GetOwner()->SetActorRotation(CloseRotation);
}

void UGlassDoor::BottlePlatformTrigAppear()
{
	if(BottlesPlatformTrig)
		BottlesPlatformTrig->SetActorLocation(FVector(-2757.0f, -3389.0f, 336.0f));		//hard-coding location of BottlePlatform trigger
	bGeneratorTrigNotUsed = false;													//setting bool to false to make sure GeneratorTrig can be used only once
}

void UGlassDoor::GlassDoorTrigAppear()
{
	if (GlassDoorTrig)
		GlassDoorTrig->SetActorLocation(FVector(-1266.0f, -3615.0f, 479.0f));	//hard-coding location of GlassDoor trigger
}

float UGlassDoor::MassOfActorsOnTrigger(ATriggerVolume* Trigger)
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
void UGlassDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//GeneratorTrigger
	if (GeneratorTrig && bGeneratorTrigNotUsed && MassOfActorsOnTrigger(GeneratorTrig) >= 600.f)	//one energy core's weight is set to 300kg
	{
		ClosingDoor();
		GlassDoorTrigAppear();
	}

	//GlassDoorTrigger
	if (GlassDoorTrig && MassOfActorsOnTrigger(GlassDoorTrig) >= 50.f)		//pawn's (player's) weight is set to 60kg
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
