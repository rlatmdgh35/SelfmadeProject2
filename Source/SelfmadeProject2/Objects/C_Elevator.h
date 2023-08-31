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
	UFUNCTION(BlueprintImplementableEvent)
		void FirstFloor_Event();

	UFUNCTION(BlueprintImplementableEvent)
		void SecondFloor_Event();

	UFUNCTION(BlueprintImplementableEvent)
		void ThirdFloor_Event();

	UFUNCTION(BlueprintImplementableEvent)
		void ForthFloor_Event();

	UFUNCTION(BlueprintImplementableEvent)
		void FifthFloor_Event();

	UFUNCTION(BlueprintCallable)
		void SetFloor(EMoveToFloor InFloor);

public:
	UPROPERTY(BlueprintReadWrite)
		EMoveToFloor MoveToFloor = EMoveToFloor::First;

	UPROPERTY(BlueprintReadWrite)
		FVector StartLocation;

	UPROPERTY(BlueprintReadWrite)
		bool bMoving;

};
