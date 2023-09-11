#include "C_Interaction.h"
#include "Components/TextBlock.h"
// #include "Player/C_Player.h" <- In Header
#include "Objects/C_Door.h"
#include "Global.h"



void UC_Interaction::BeginPlay(ACharacter* InCharacter)
{
	Player = Cast<AC_Player>(InCharacter);

	Player->InteractionText.AddDynamic(this, &UC_Interaction::InteractionText);

	TArray<AActor*> doorActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Door::StaticClass(), doorActors);
	for (int32 i = 0; i < doorActors.Num(); i++)
		Doors.Add(Cast<AC_Door>(doorActors[i]));

}

void UC_Interaction::InteractionText(EInteractionType InType)
{
	CheckFalse(Player->InteractionType == EInteractionType::None);

	switch (InType)
	{
	case EInteractionType::None:
		ClearTextBlock();
		break;
	case EInteractionType::Door:
		DoorTextBlock();
		break;
	case EInteractionType::Lock:
		ElevatorTextBlock();
		break;
	case EInteractionType::Elevator:
		LockTextBlock();
		break;
	}


}

void UC_Interaction::ClearTextBlock()
{
	MainText->SetText(FText::FromString(""));
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
	MainText->SetText(ElevatorText);
}

void UC_Interaction::LockTextBlock()
{
	MainText->SetText(LockText);
}

