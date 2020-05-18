// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpeningDoor(float DeltaTime);
	void ClosingDoor(float DeltaTime);
	
private:

	FRotator CurrentRotation;
	FRotator OpenRotation;
	FRotator CloseRotation;
	FRotator Door = { 0.f, 0.f, 0.f };
	float LastDoorOpened = 0.f;
	UPROPERTY(EditAnywhere)
		float CloseDoorDelay = 0.4f;
	UPROPERTY(EditAnywhere)
		float Target = 90.f;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate;
	UPROPERTY(EditAnywhere)
		AActor* OneThatOpens;
};
