#pragma once

#include "CoreMinimal.h"
#include "Objects/C_Elevator.h"
#include "C_Elevator_Button.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractionElevatorSignature);

UCLASS()
class SELFMADEPROJECT2_API AC_Elevator_Button : public AC_Elevator
{
	GENERATED_BODY()

public:
	AC_Elevator_Button();
	
protected:
	virtual void BeginPlay() override;

public:
	void Interaction();

public:
	FInteractionElevatorSignature InteractionElevator;

public:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UStaticMeshComponent* Button;

public:
	UPROPERTY(EditAnywhere)
		EMoveToFloor Floor;

	UPROPERTY(EditAnywhere)
		bool bIn;

private:
	AC_Elevator* Elevator;

public:
	bool bCanCall = false;

};
