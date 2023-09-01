#include "C_Elevator.h"
#include "C_Elevator_Button.h"
#include "Global.h"


void AC_Elevator::BeginPlay()
{
	TArray<AActor*> buttonActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Elevator_Button::StaticClass(), buttonActor);
	Button = Cast<AC_Elevator_Button>(buttonActor[0]);

	Button->SetFloorDelegate.AddDynamic(this, &AC_Elevator::OpenElevatorDoor);
}

void AC_Elevator::SetFloor(EMoveToFloor InFloor)
{
	CheckFalse(bCloseDoor);

	MoveToFloor = InFloor;
	StartLocation = GetActorLocation();
	bMoving = true;
}