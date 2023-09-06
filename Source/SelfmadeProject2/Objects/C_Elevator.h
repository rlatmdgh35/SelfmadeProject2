#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Elevator.generated.h"


UENUM(BlueprintType)
enum class EMoveToFloor : uint8
{
	Zero, First, Second, Third, Forth, Fifth, Arrow
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
		void DoMoveDoor(EMoveToFloor Type);

	UFUNCTION(BlueprintImplementableEvent)
		void CloseDoor(EMoveToFloor Type);

protected:
	UFUNCTION(BlueprintCallable)
		void ResetButtonColor();

	void ChangeColor();

public:
	void SetFloor(EMoveToFloor InFloor);

private:
	TArray<class AC_Elevator_Button*> Buttons;

public:
	UPROPERTY(BlueprintReadOnly)
		int32 MoveToFloor = 1;

	UPROPERTY(BlueprintReadWrite)
		FVector StartLocation;

	UPROPERTY(BlueprintReadWrite)
		bool bMoving = false;

	UPROPERTY(BlueprintReadWrite)
		bool bCloseDoor = true;

public:
	UPROPERTY(BlueprintReadOnly)
		bool IsOpenTenth = false;


};
