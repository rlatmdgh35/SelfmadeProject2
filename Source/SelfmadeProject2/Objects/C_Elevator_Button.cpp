#include "C_Elevator_Button.h"
#include "Components/StaticMeshComponent.h"
#include "Player/C_Player.h"
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
	FVector resultLocation = elevatorLocation + FVector(-130.f, -137.5f, (110.f + 20.f * (float)Floor));

	if ((float)Floor != 3)
	{
		SetActorLocation(resultLocation);
	}
	
	else if (Player->DataAsset->OpenGuide.IsOpenTenth == true)
	{
		SetActorLocation(resultLocation);
	}
}

void AC_Elevator_Button::Interaction()
{
	CheckTrue(Elevator->bMoving == true);

	C_Log::Print((int)Floor + 1);

	if (Elevator->MoveToFloor != Floor)
	{
		Elevator->SetFloor(Floor);
	}
	else if (PressElevatorButton.IsBound())
	{
		PressElevatorButton.Broadcast();
	}
}