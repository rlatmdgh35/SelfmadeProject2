#include "C_Elevator_Button.h"
#include "Components/StaticMeshComponent.h"
#include "Global.h"


AC_Elevator_Button::AC_Elevator_Button()
{
	C_Helpers::CreateSceneComponent<UStaticMeshComponent>(this, &Button, "Button", RootComponent);

	Elevator = Cast<AC_Elevator>(GetParentActor());
}

void AC_Elevator_Button::MoveOtherFloor()
{
	if (Elevator->MoveToFloor != Floor)
		Elevator->SetFloor(Floor);
}

