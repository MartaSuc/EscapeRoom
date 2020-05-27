// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Door.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM_API UDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoor();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void FindTriggers();
	void OpeningDoor(float DeltaTime);
	void ClosingDoor();
	void BottlePlatformTrigAppear();
	void DoorTrigAppear();
	float MassOfActorsOnTrigger(ATriggerVolume* Trigger);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	FVector CurrentLocation = { 0.f, 0.f, 0.f };
	FVector OpenLocation = { 0.f, 0.f, 0.f };
	FVector CloseLocation = { 0.f, 0.f, 0.f };
	FVector Door = { 0.f, 0.f, 0.f };
	bool bGeneratorTrigNotUsed = true;
	float TargetX = -11.f;

	UPROPERTY(EditAnywhere)
		float TargetY = 100.f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* GeneratorTrig = nullptr;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* DoorTrig = nullptr;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* TrapRoomTrig1 = nullptr;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* TrapRoomTrig2 = nullptr;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* TrapRoomTrig3 = nullptr;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* TrapRoomTrig4 = nullptr;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* BottlesPlatformTrig = nullptr;
		
};
