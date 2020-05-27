#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Exit.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM_API UExit : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UExit();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void FindTrigger();
	float MassOfActorsOnTrigger(ATriggerVolume* Trigger);
	void OpeningDoor(float DeltaTime);
	void ClosingDoor(float DeltaTime);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	FVector CurrentLocation = { 0.f, 0.f, 0.f };
	FVector OpenLocation = { 0.f, 0.f, 0.f };
	FVector CloseLocation = { 0.f, 0.f, 0.f };
	FVector Door = { 0.f, 0.f, 0.f };

	UPROPERTY(EditAnywhere)
		ATriggerVolume* ExitDoorTrig = nullptr;
		
	AActor* OneThatOpens = nullptr;
};
