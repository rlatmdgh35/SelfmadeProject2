#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Elevator.generated.h"


UENUM(BlueprintType)
enum class EMoveToFloor : uint8
{
	Arrow, First, Second, Third, Forth, Fifth
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
	void SetFloor(EMoveToFloor InFloor);

	UFUNCTION(BlueprintImplementableEvent)
		void DoMoveDoor(EMoveToFloor Type);

	UFUNCTION(BlueprintImplementableEvent)
		void CloseDoor(EMoveToFloor Type);

	UFUNCTION(BlueprintCallable)
		void ChangeColor();

	UFUNCTION(BlueprintCallable)
		void ResetButtonColor();


protected:
	UPROPERTY(BlueprintReadOnly)
		class USceneComponent* RootSceneComponent;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* TopMesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

protected:
	class AC_Player* Player;

private:
	TArray<class AC_Elevator_Button*> Buttons;
	TArray<class AC_Elevator_OutDoor*> OutDoors;

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		EMoveToFloor MoveToFloor = EMoveToFloor::First;

	UPROPERTY(BlueprintReadWrite)
		int32 CurrentFloor;

	UPROPERTY(BlueprintReadWrite)
		FVector StartLocation;

	UPROPERTY(BlueprintReadWrite)
		bool bMoving = false;

	UPROPERTY(BlueprintReadWrite)
		bool bCloseDoor = true;

	UPROPERTY(BlueprintReadWrite)
		bool bMovingDoor;

};
