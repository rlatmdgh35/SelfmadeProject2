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

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintImplementableEvent)
		void DoMoveDoor();

public:
	void SetFloor(EMoveToFloor InFloor);

private:
	TArray<class AC_Elevator_Button*> Buttons;


public:
	UPROPERTY(BlueprintReadWrite)
		EMoveToFloor MoveToFloor = EMoveToFloor::First;

	UPROPERTY(BlueprintReadWrite)
		FVector StartLocation;

	UPROPERTY(BlueprintReadWrite)
		bool bMoving = false;

	UPROPERTY(BlueprintReadWrite)
		bool bCloseDoor;

public:
	UPROPERTY(BlueprintReadOnly)
		bool IsOpenTenth = false;

};
