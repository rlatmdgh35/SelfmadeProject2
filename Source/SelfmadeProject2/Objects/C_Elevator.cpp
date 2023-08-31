#include "C_Elevator.h"


void AC_Elevator::SetFloor(EMoveToFloor InFloor)
{
	MoveToFloor = InFloor;
	StartLocation = GetActorLocation();
	bMoving = true;
}