#include "C_LineOfCharacter.h"
#include "Components/TextBlock.h"
#include "GameFramework/Character.h"
#include "Objects/C_Loop.h"
#include "Global.h"



void UC_LineOfCharacter::BeginPlay(ACharacter* InCharacter)
{
	Player = Cast<AC_Player>(InCharacter);
	Player->CharacterLineType.AddDynamic(this, &UC_LineOfCharacter::SetCharacterLine);
	
	TArray<AActor*> loopActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Loop::StaticClass(), loopActor);
	if (loopActor.Num() > 0)
		Loop = Cast<AC_Loop>(loopActor[0]);
}


void UC_LineOfCharacter::SetCharacterLine(ECharacterLineType InType)
{
	switch (InType)
	{
	case ECharacterLineType::StartMap_Start:
		PrintStartMap_1();
		break;
	case ECharacterLineType::StartMap_Light:
		PrintStartMap_4();
		break;
	case ECharacterLineType::StartMap_JumpScare:
		PrintStartMap_5();
		break;
	case ECharacterLineType::StartMap_End:
		PrintStartMap_6();
		break;
	case ECharacterLineType::StartMap_Loop:
		PrintStartMap_7();
		break;
	case ECharacterLineType::PastMap_Start:
		PrintPastMap_1();
		break;
	case ECharacterLineType::HotelMap_Start:
		break;
	case ECharacterLineType::OpenEighthGuide:
		PrintHotelMap_Eighth();
		break;
	case ECharacterLineType::OpenNinthGuide:
		PrintHotelMap_Ninth();
		break;
	case ECharacterLineType::OpenTenthGuide:
		PrintHotelMap_Tenth1();
		break;
	}
}

void UC_LineOfCharacter::ClearTextBlock()
{
	CharacterLineText->SetText(FText::FromString(""));

	if (bBoth == true)
		OtherPersonLineText->SetText(FText::FromString(""));
}

void UC_LineOfCharacter::ClearTextTimer(float InRate, bool Both)
{
	bBoth = Both;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UC_LineOfCharacter::ClearTextBlock, InRate);
}

void UC_LineOfCharacter::BlockPlayer()
{
	Player->bStopLocation = true;
	Player->bStopRotation = true;
}

void UC_LineOfCharacter::NotBlockPlayer()
{
	Player->bStopLocation = false;
	Player->bStopRotation = false;
}

void UC_LineOfCharacter::ControllPlayerTimer(float InRate, bool BlockPlayer)
{
	if (BlockPlayer)
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UC_LineOfCharacter::BlockPlayer, InRate);
	else
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UC_LineOfCharacter::NotBlockPlayer, InRate);
}

void UC_LineOfCharacter::PrintStartMap_1()
{
	CharacterLineText->SetText(StartMap_1);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UC_LineOfCharacter::PrintPastMap_2, 1.5);
}

void UC_LineOfCharacter::PrintStartMap_2()
{
	CharacterLineText->SetText(StartMap_2);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UC_LineOfCharacter::PrintPastMap_3, 2.5);
}

void UC_LineOfCharacter::PrintStartMap_3()
{
	CharacterLineText->SetText(StartMap_3);

	ClearTextTimer(3.5f);
}

void UC_LineOfCharacter::PrintStartMap_4()
{
	CharacterLineText->SetText(StartMap_4);

	ClearTextTimer(4.5f);
}

void UC_LineOfCharacter::PrintStartMap_5()
{
	CharacterLineText->SetText(StartMap_5);

	ClearTextTimer(4.f);
}

void UC_LineOfCharacter::PrintStartMap_6()
{
	CharacterLineText->SetText(StartMap_6);

	ClearTextTimer(2.75f);
}

void UC_LineOfCharacter::PrintStartMap_7()
{
	OtherPersonLineText->SetText(StartMap_7);
}

void UC_LineOfCharacter::PrintPastMap_1()
{
	CharacterLineText->SetText(PastMap_1);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UC_LineOfCharacter::PrintPastMap_2, 5.5);
}

void UC_LineOfCharacter::PrintPastMap_2()
{
	CharacterLineText->SetText(PastMap_2);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UC_LineOfCharacter::PrintPastMap_3, 6);
}

void UC_LineOfCharacter::PrintPastMap_3()
{
	CharacterLineText->SetText(PastMap_3);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UC_LineOfCharacter::PrintPastMap_4, 5);
}

void UC_LineOfCharacter::PrintPastMap_4()
{
	CharacterLineText->SetText(PastMap_4);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UC_LineOfCharacter::PrintPastMap_5, 7);
}

void UC_LineOfCharacter::PrintPastMap_5()
{
	Loop->bLoop = false;

	ClearTextBlock();
}

void UC_LineOfCharacter::PrintHotelMap_1()
{
	OtherPersonLineText->SetText(HotelMap_1);
}

void UC_LineOfCharacter::PrintHotelMap_2()
{
	OtherPersonLineText->SetText(HotelMap_2);
}

void UC_LineOfCharacter::PrintHotelMap_3()
{
	CharacterLineText->SetText(HotelMap_3);
}

void UC_LineOfCharacter::PrintHotelMap_4()
{
	OtherPersonLineText->SetText(HotelMap_4);
}

void UC_LineOfCharacter::PrintHotelMap_5()
{
	OtherPersonLineText->SetText(HotelMap_5);
}

void UC_LineOfCharacter::PrintHotelMap_6()
{
	OtherPersonLineText->SetText(HotelMap_6);
}

void UC_LineOfCharacter::PrintHotelMap_7()
{
	OtherPersonLineText->SetText(HotelMap_7);
}

void UC_LineOfCharacter::PrintHotelMap_8()
{
	OtherPersonLineText->SetText(HotelMap_8);
}

void UC_LineOfCharacter::PrintHotelMap_9()
{
	OtherPersonLineText->SetText(HotelMap_9);
}

void UC_LineOfCharacter::PrintHotelMap_Eighth()
{
	CharacterLineText->SetText(OpenEighthGuide);

	ClearTextTimer(3.5f);
}

void UC_LineOfCharacter::PrintHotelMap_Ninth()
{
	CharacterLineText->SetText(OpenNinthGuide);

	ClearTextTimer(3.5f);
}

void UC_LineOfCharacter::PrintHotelMap_Tenth1()
{
	CharacterLineText->SetText(OpenTenthGuide1);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UC_LineOfCharacter::PrintHotelMap_Tenth2, 4);
}

void UC_LineOfCharacter::PrintHotelMap_Tenth2()
{
	CharacterLineText->SetText(OpenTenthGuide2);

	ClearTextTimer(3.5f);
}

