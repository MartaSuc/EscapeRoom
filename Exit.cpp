#include "Exit.h"

// Sets default values for this component's properties
UExit::UExit()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UExit::BeginPlay()
{
	Super::BeginPlay();
	FindTrigger();

	CurrentLocation = GetOwner()->GetActorLocation();
	OpenLocation = CloseLocation = CurrentLocation;
	OpenLocation += {.0f, .0f, 310.0f};				//setting open location to {-830, -3990, 503}
}

void UExit::FindTrigger()
{
	if (!ExitDoorTrig) UE_LOG(LogTemp, Error, TEXT("%s has no ExitDoorTrig set"), *GetOwner()->GetName());
}

float UExit::MassOfActorsOnTrigger(ATriggerVolume* Trigger)
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

void UExit::OpeningDoor(float DeltaTime)
{
	CurrentLocation = GetOwner()->GetActorLocation();
	Door = FMath::Lerp(CurrentLocation, OpenLocation, DeltaTime * 0.2f);
	GetOwner()->SetActorLocation(Door);
}

void UExit::ClosingDoor(float DeltaTime)
{
	CurrentLocation = GetOwner()->GetActorLocation();
	Door = FMath::Lerp(CurrentLocation, CloseLocation, DeltaTime * 1.9f);
	GetOwner()->SetActorLocation(Door);
}

// Called every frame
void UExit::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ExitDoorTrig && MassOfActorsOnTrigger(ExitDoorTrig) >= 80.f)		//weight of 4 boxes from TrapRoom
		OpeningDoor(DeltaTime);
	else ClosingDoor(DeltaTime);
}
