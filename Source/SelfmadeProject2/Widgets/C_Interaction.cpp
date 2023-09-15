#include "C_Interaction.h"
#include "Components/TextBlock.h"
// #include "Player/C_Player.h" <- In Header
#include "Officer/C_Security_Officer.h"
#include "Objects/C_LightSwitch.h"
#include "Objects/C_Door.h"
#include "Objects/C_Elevator_Button.h" // C_Elevator_Button.h 's parent is C_Elevator
#include "Global.h"



void UC_Interaction::BeginPlay(ACharacter* InCharacter)
{
	Player = Cast<AC_Player>(InCharacter);

	Player->InteractionText.AddDynamic(this, &UC_Interaction::InteractionText);

	TArray<AActor*> lightSwitchActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_LightSwitch::StaticClass(), lightSwitchActors);
	for (int32 i = 0; i < lightSwitchActors.Num(); i++)
		LightSwitches.Add(Cast<AC_LightSwitch>(lightSwitchActors[i]));

	TArray<AActor*> doorActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Door::StaticClass(), doorActors);
	for (int32 i = 0; i < doorActors.Num(); i++)
		Doors.Add(Cast<AC_Door>(doorActors[i]));

	TArray<AActor*> elevatorButtonActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Elevator_Button::StaticClass(), elevatorButtonActors);
	for (int32 i = 0; i < elevatorButtonActors.Num(); i++)
		Buttons.Add(Cast<AC_Elevator_Button>(elevatorButtonActors[i]));

	TArray<AActor*> elevatorActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Elevator::StaticClass(), elevatorActor);
	if (elevatorActor.Num() > 0)
		Elevator = Cast<AC_Elevator>(elevatorActor[0]);

}

void UC_Interaction::InteractionText(EInteractionType InType)
{
	switch (InType)
	{
	case EInteractionType::None:
		ClearTextBlock();
		break;
	case EInteractionType::LightSwitch:
		LightTextBlock();
		break;
	case EInteractionType::Officer:
		StartOfficerTextBlock();
		break;
	case EInteractionType::Door:
		DoorTextBlock();
		break;
	case EInteractionType::Elevator:
		ElevatorTextBlock();
		break;
	case EInteractionType::Lock:
		LockTextBlock();
		break;
	}
}

void UC_Interaction::ClearTextBlock()
{
	MainText->SetText(FText::FromString(""));
}

void UC_Interaction::LightTextBlock()
{
	for (int32 i = 0; i < LightSwitches.Num(); i++)
	{
		if (LightSwitches[i]->bIsOnLight != true)		MainText->SetText(OnLightText);
		else											MainText->SetText(OffLightText);
	}
}

void UC_Interaction::StartOfficerTextBlock()
{
	CheckFalse(Player->Officer->bLoop == true);

	MainText->SetText(StartOfficerText);
}

void UC_Interaction::DoorTextBlock()
{
	for (int32 i = 0; i < Doors.Num(); i++)
	{
		if((Doors[i]->bOpen == false) && (Doors[i]->bMoving == false))		MainText->SetText(OpenDoorText);
		if((Doors[i]->bOpen == false) && (Doors[i]->bMoving == false))		MainText->SetText(CloseDoorText);
		if((Doors[i]->bOpen == false) && (Doors[i]->bMoving == false))		MainText->SetText(CloseDoorText);
		if((Doors[i]->bOpen == false) && (Doors[i]->bMoving == false))		MainText->SetText(OpenDoorText);
	}
}

void UC_Interaction::ElevatorTextBlock()
{
	for (int32 i = 0; i < Buttons.Num(); i++)
	{
		CheckTrue(Elevator->bMoving == true);
		if (Buttons[i]->bCanCall == true)
		{
			if (Buttons[i]->Floor == EMoveToFloor::Arrow)
			{
				if (Buttons[i]->bOpenButton == true)
				{
					C_Log::Log("Open");
					MainText->SetText(OpenDoorText);
				}
				else
				{
					C_Log::Log("Close");
					MainText->SetText(CloseDoorText);
				}
			}
			else if (Elevator->bMovingDoor == false)
				MainText->SetText(ElevatorText);
		}
	}

	MainText->SetText(ElevatorText);
}

void UC_Interaction::LockTextBlock()
{
	MainText->SetText(LockText);
}

