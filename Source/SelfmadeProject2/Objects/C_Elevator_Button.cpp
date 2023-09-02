#include "C_Elevator_Button.h"
#include "Components/StaticMeshComponent.h"
#include "Player/C_Player.h"
#include "Global.h"


AC_Elevator_Button::AC_Elevator_Button()
{
	C_Helpers::CreateSceneComponent<UStaticMeshComponent>(this, &Button, "Button", RootComponent);
	
	// Todo. GetParent();
	/*
	Elevator = Cast<AC_Elevator>(GetParentActor());
	*/
}

void AC_Elevator_Button::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> elevatorActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Elevator::StaticClass(), elevatorActor);
	Elevator = Cast<AC_Elevator>(elevatorActor[0]);
}

void AC_Elevator_Button::Interaction()
{
	CheckTrue(Elevator->bMoving == true);

	if (Elevator->MoveToFloor != Floor)
	{
		if (bIn == true)
			Elevator->SetFloor(Floor);
		// elevator->
	}
	else
	{
		C_Log::Print("Test");
		if (InteractionElevator.IsBound())
			InteractionElevator.Broadcast();
	}
}