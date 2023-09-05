#include "C_Elevator.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInstanceConstant.h"
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

void AC_Elevator::ChangeColor()
{
	DynamicMaterial->SetVectorParameterValue("Param", FLinearColor(1, 0, 0));

	for (uint8 i = 0; i < Buttons.Num(); i++)
	{
		if (Buttons[i]->Floor == EMoveToFloor::Arrow)
		{
			FTimerHandle timerhandle;
			GetWorldTimerManager().SetTimer(timerhandle, this, &AC_Elevator::ResetButtonColor, 2);
		}
	}
}

void AC_Elevator::ResetButtonColor()
{
	DynamicMaterial->SetVectorParameterValue("Param", FLinearColor(0, 1, 0));
}