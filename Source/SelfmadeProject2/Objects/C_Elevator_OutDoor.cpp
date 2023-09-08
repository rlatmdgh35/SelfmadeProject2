#include "C_Elevator_OutDoor.h"
#include "Components/TextRenderComponent.h"
#include "C_Elevator_Button.h"
#include "Global.h"



AC_Elevator_OutDoor::AC_Elevator_OutDoor()
{
	C_Helpers::CreateSceneComponent<USceneComponent>(this, &DefaultSceneComponent, "DefaultSceneComponent");

	C_Helpers::CreateSceneComponent<UStaticMeshComponent>(this, &RightDoor, "RightDoor", DefaultSceneComponent);
	C_Helpers::CreateSceneComponent<UStaticMeshComponent>(this, &LeftDoor, "LeftDoor", DefaultSceneComponent);
	C_Helpers::CreateSceneComponent<UTextRenderComponent>(this, &Text, "Text", DefaultSceneComponent);

	RightDoor->SetRelativeLocation(FVector(0, -75, 150));
	RightDoor->SetRelativeScale3D(FVector(0.1f, 1.5f, 3.f));

	LeftDoor->SetRelativeLocation(FVector(0, 75, 150));
	LeftDoor->SetRelativeScale3D(FVector(0.1f, 1.5f, 3.f));

	Text->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	Text->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
	Text->SetRelativeLocationAndRotation(FVector(-50, 180, 160), FRotator(0, 180, 0)); // Todo. Need Fix Location
}

void AC_Elevator_OutDoor::BeginPlay()
{
	Super::BeginPlay();
	
	Location_R = RightDoor->GetRelativeLocation();
	Location_L = LeftDoor->GetRelativeLocation();
}




