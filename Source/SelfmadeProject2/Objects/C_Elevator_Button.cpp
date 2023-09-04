#include "C_Elevator_Button.h"
#include "Components/StaticMeshComponent.h"
#include "Player/C_Player.h"
#include "Component/C_PlayerComponent.h"
#include "DataAsset/C_DataAsset.h"
#include "Global.h"


AC_Elevator_Button::AC_Elevator_Button()
{
	PrimaryActorTick.bCanEverTick = true;

	C_Helpers::CreateSceneComponent<UStaticMeshComponent>(this, &ButtonMesh, "Button", RootComponent);
}

void AC_Elevator_Button::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> elevatorActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Elevator::StaticClass(), elevatorActor);
	for (uint8 i = 0; i < elevatorActor.Num(); i++)
	{
		if (elevatorActor[i]->Tags.Num() > 0)
		{
			if (elevatorActor[i]->Tags[0] == FName("Elevator"))
				Elevator = Cast<AC_Elevator>(elevatorActor[i]);
		}
	}

	TArray<AActor*> playerActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Player::StaticClass(), playerActor);
	Player = Cast<AC_Player>(playerActor[0]);
}

void AC_Elevator_Button::Tick(float DeltaTime)
{
	CheckFalse(bInElevator);

	Super::Tick(DeltaTime);

	FVector elevatorLocation = Elevator->GetActorLocation();

	if (Floor != EMoveToFloor::Arrow)
	{
		FVector resultLocation = elevatorLocation + FVector(-132.f, -137.5f, (110.f + 20.f * (float)Floor));

		if ((float)Floor != 3) // Not ForthButtons
			SetActorLocation(resultLocation);

		else if (Player->PlayerComponent->DataAsset->OpenGuide.IsOpenTenth == true)
			SetActorLocation(resultLocation);
	}
	else
	{
		FVector resultLocation = elevatorLocation + FVector(-132, (-150 + 25 * bOpenButton), 90);	// If bOpenButton == true -> SetLocation(-132, -125, 90)
																									// If bOpenButton == false -> SetLocation(-132, -150, 90);
		SetActorLocation(resultLocation);
	}
}

void AC_Elevator_Button::Interaction()
{
	CheckTrue(Elevator->bMoving == true);
	CheckFalse(Elevator->bCloseDoor == true || Floor == EMoveToFloor::Arrow);

	if (Floor != EMoveToFloor::Arrow)
	{
		if (Elevator->MoveToFloor != Floor)
			Elevator->SetFloor(Floor);

		else if (PressOpenDoorButton.IsBound())
			PressOpenDoorButton.Broadcast(Floor);
	}
	else if ((bOpenButton == true) && (PressOpenDoorButton.IsBound()))
		PressOpenDoorButton.Broadcast(Floor);

	else if (PressCloseDoorButton.IsBound())
		PressCloseDoorButton.Broadcast(Floor);

}