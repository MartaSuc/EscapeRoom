#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "GlassDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM_API UGlassDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGlassDoor();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void FindTriggers();
	void OpeningDoor(float DeltaTime);
	void ClosingDoor();
	void BottlePlatformTrigAppear();
	void GlassDoorTrigAppear();
	float MassOfActorsOnTrigger(ATriggerVolume* Trigger);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	FRotator CurrentRotation = { 0.f, 0.f, 0.f };
	FRotator OpenRotation = { 0.f, 0.f, 0.f };
	FRotator CloseRotation = { 0.f, 0.f, 0.f };
	FRotator Door = { 0.f, 0.f, 0.f };
	bool bGeneratorTrigNotUsed = true;

	UPROPERTY(EditAnywhere)
		float Target = 90.f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* GeneratorTrig = nullptr;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* GlassDoorTrig = nullptr;
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
