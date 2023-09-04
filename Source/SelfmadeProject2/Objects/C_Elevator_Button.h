#pragma once

#include "CoreMinimal.h"
#include "Objects/C_Elevator.h"
#include "C_Elevator_Button.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPressOpenDoorButtonSignature, EMoveToFloor, InType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPressCloseDoorButtonSignature, EMoveToFloor, InType);

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
	FPressOpenDoorButtonSignature PressOpenDoorButton;
	FPressCloseDoorButtonSignature PressCloseDoorButton;

public:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* ButtonMesh;

private:
	class AC_Player* Player;

public:
	UPROPERTY(EditAnywhere)
		EMoveToFloor Floor;

	UPROPERTY(EditAnywhere)
		bool bInElevator;

	UPROPERTY(EditAnywhere)
		bool bOpenButton;

public:
	UPROPERTY(BlueprintReadOnly)
		AC_Elevator* Elevator;

public:
	bool bCanCall = false;

};
