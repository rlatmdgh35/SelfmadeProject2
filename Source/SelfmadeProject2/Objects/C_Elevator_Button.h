#pragma once

#include "CoreMinimal.h"
#include "Objects/C_Elevator.h"
#include "C_Elevator_Button.generated.h"

UCLASS()
class SELFMADEPROJECT2_API AC_Elevator_Button : public AC_Elevator
{
	GENERATED_BODY()

public:
	AC_Elevator_Button();
	void MoveOtherFloor();

public:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UStaticMeshComponent* Button;

private:
	AC_Elevator* Elevator;

public:
	UPROPERTY(EditAnywhere)
		EMoveToFloor Floor;

};
