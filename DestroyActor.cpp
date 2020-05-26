#include "DestroyActor.h"

// Sets default values for this component's properties
UDestroyActor::UDestroyActor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UDestroyActor::BeginPlay()
{
	Super::BeginPlay();
	FindTrigger();
}

void UDestroyActor::FindTrigger()
{
	if (!BottlesPlatformTrig) UE_LOG(LogTemp, Error, TEXT("%s has no BottlesPlatformTrig set"), *GetOwner()->GetName());
}

void UDestroyActor::Destroy()
{
	GetOwner()->Destroy();
}

float UDestroyActor::MassOfActorsOnTrigger(ATriggerVolume* Trigger)
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
void UDestroyActor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (BottlesPlatformTrig && MassOfActorsOnTrigger(BottlesPlatformTrig) >= 50.f)	//pawn's (player's) weight is set to 60kg
	{
	if (!GetOwner()->Destroy())
		Destroy();
	}
}
