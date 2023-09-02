#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Elevator.generated.h"


UENUM(BlueprintType)
enum class EMoveToFloor : uint8
{
	First, Second, Third, Forth, Fifth
};

UCLASS()
class SELFMADEPROJECT2_API AC_Elevator : public AActor
{
	GENERATED_BODY()

public:
	AC_Elevator();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintImplementableEvent)
		void OpenElevatorDoor();

public:
	void SetFloor(EMoveToFloor InFloor);

private:
	class AC_Elevator_Button* Button;


public:
	UPROPERTY(BlueprintReadWrite)
		EMoveToFloor MoveToFloor = EMoveToFloor::First;

	UPROPERTY(BlueprintReadWrite)
		FVector StartLocation;

	UPROPERTY(BlueprintReadWrite)
		bool bMoving = false;

	UPROPERTY(BlueprintReadWrite)
		bool bCloseDoor;




};
