#include "C_Elevator.h"
#include "C_Elevator_Button.h"
#include "Global.h"




void AC_Elevator::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> buttonActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Elevator_Button::StaticClass(), buttonActors);
	
	for (uint8 i = 0; i < buttonActors.Num(); i++)
	{
		Buttons.Add(Cast<AC_Elevator_Button>(buttonActors[i]));
		Buttons[i]->PressOpenDoorButton.AddDynamic(this, &AC_Elevator::DoMoveDoor);
		Buttons[i]->PressCloseDoorButton.AddDynamic(this, &AC_Elevator::CloseDoor);
	}
}

void AC_Elevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AC_Elevator::SetFloor(EMoveToFloor InFloor)
{
	CheckFalse(bCloseDoor);

	StartLocation = GetActorLocation();
	MoveToFloor = InFloor;
	bMoving = true;
}
