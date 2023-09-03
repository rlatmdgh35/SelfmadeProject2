#pragma once

#include "CoreMinimal.h"
#include "Objects/C_Elevator.h"
#include "C_Elevator_Button.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPressElevatorButtonSignature);

UCLASS()
class SELFMADEPROJECT2_API AC_Elevator_Button : public AC_Elevator
{
	GENERATED_BODY()

public:
	AC_Elevator_Button();
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	void Interaction();

public:
	FPressElevatorButtonSignature PressElevatorButton;

public:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UStaticMeshComponent* ButtonMesh;

private:
	class AC_Player* Player;

public:
	UPROPERTY(EditAnywhere)
		EMoveToFloor Floor;

	UPROPERTY(EditAnywhere)
		bool bInElevator;

public:
	UPROPERTY(BlueprintReadOnly)
		AC_Elevator* Elevator;

public:
	UPROPERTY(BlueprintReadWrite)
		bool bCanCall = false;

};
