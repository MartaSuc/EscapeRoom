// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "GameInfo.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM_API UGameInfo : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGameInfo();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void FindTriggers();
	void PrintStartMessage();
	void PrintEndGameMessage();
	void Rotate(float DeltaTime);
	float MassOfActorsOnTrigger(ATriggerVolume* Trigger);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		ATriggerVolume* StartInfoTrig = nullptr;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* EndGameTrig = nullptr;

	FRotator CurrentRotation = { 0.f, 0.f, 0.f };
	FRotator StopRotation = { 0.f, 0.f, 0.f };
	FRotator CubeRotation = { 0.f, 0.f, 0.f };

	float Time = 0.f;
	bool bStopTime = false;
};
