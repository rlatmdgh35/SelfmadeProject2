#include "C_Elevator_OutDoor.h"
#include "C_Elevator_Button.h"
#include "Global.h"



AC_Elevator_OutDoor::AC_Elevator_OutDoor()
{
	C_Helpers::CreateSceneComponent<USceneComponent>(this, &DefaultSceneComponent, "DefaultSceneComponent");

	C_Helpers::CreateSceneComponent<UStaticMeshComponent>(this, &RightDoor, "RightDoor", DefaultSceneComponent);
	C_Helpers::CreateSceneComponent<UStaticMeshComponent>(this, &LeftDoor, "LeftDoor", DefaultSceneComponent);

	RightDoor->SetRelativeLocation(FVector(0, -75, 150));
	RightDoor->SetRelativeScale3D(FVector(0.1f, 1.5f, 3.f));

	LeftDoor->SetRelativeLocation(FVector(0, 75, 150));
	LeftDoor->SetRelativeScale3D(FVector(0.1f, 1.5f, 3.f));
}

void AC_Elevator_OutDoor::BeginPlay()
{
	Super::BeginPlay();
	
	Location_R = RightDoor->GetRelativeLocation();
	Location_L = LeftDoor->GetRelativeLocation();
}




