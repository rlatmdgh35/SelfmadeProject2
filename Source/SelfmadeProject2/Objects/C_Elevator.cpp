#include "C_Elevator.h"
#include "C_Elevator_Button.h"
#include "Global.h"

AC_Elevator::AC_Elevator()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AC_Elevator::BeginPlay()
{
	TArray<AActor*> buttonActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Elevator_Button::StaticClass(), buttonActor);
	Button = Cast<AC_Elevator_Button>(buttonActor[0]);

	Button->InteractionElevator.AddDynamic(this, &AC_Elevator::OpenElevatorDoor);
}

void AC_Elevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AC_Elevator::SetFloor(EMoveToFloor InFloor)
{
	CheckFalse(bCloseDoor);

	MoveToFloor = InFloor;
	StartLocation = GetActorLocation();
	bMoving = true;
}