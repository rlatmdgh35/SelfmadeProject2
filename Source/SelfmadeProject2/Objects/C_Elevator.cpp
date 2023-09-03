#include "C_Elevator.h"
#include "C_Elevator_Button.h"
#include "Global.h"




void AC_Elevator::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> buttonActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Elevator_Button::StaticClass(), buttonActors);
	if (buttonActors.Num() > 0)
	{
		for (uint8 i = 0; i < buttonActors.Num(); i++)
		{
			Buttons.Add(Cast<AC_Elevator_Button>(buttonActors[i]));
			Buttons[i]->PressElevatorButton.AddDynamic(this, &AC_Elevator::DoMoveDoor);
		}
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
