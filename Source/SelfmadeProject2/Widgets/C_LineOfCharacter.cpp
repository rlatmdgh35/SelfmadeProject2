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
	case ECharacterLineType::StartMap_JumpScare:
		PrintStartMap_5();
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
}

void UC_LineOfCharacter::ClearTextTimer(float InRate)
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UC_LineOfCharacter::ClearTextBlock, InRate);
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
}

void UC_LineOfCharacter::PrintStartMap_5()
{
	CharacterLineText->SetText(StartMap_5);

	ClearTextTimer(3.5f);
}

void UC_LineOfCharacter::PrintStartMap_6()
{
}

void UC_LineOfCharacter::PrintStartMap_7()
{
	CharacterLineText->SetText(StartMap_7);

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
	CharacterLineText->SetText(HotelMap_1);
}

void UC_LineOfCharacter::PrintHotelMap_2()
{
	CharacterLineText->SetText(HotelMap_2);
}

void UC_LineOfCharacter::PrintHotelMap_3()
{
	CharacterLineText->SetText(HotelMap_3);
}

void UC_LineOfCharacter::PrintHotelMap_4()
{
	CharacterLineText->SetText(HotelMap_4);
}

void UC_LineOfCharacter::PrintHotelMap_5()
{
	CharacterLineText->SetText(HotelMap_5);
}

void UC_LineOfCharacter::PrintHotelMap_6()
{
	CharacterLineText->SetText(HotelMap_6);
}

void UC_LineOfCharacter::PrintHotelMap_7()
{
	CharacterLineText->SetText(HotelMap_7);
}

void UC_LineOfCharacter::PrintHotelMap_8()
{
	CharacterLineText->SetText(HotelMap_8);
}

void UC_LineOfCharacter::PrintHotelMap_9()
{
	CharacterLineText->SetText(HotelMap_9);
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

