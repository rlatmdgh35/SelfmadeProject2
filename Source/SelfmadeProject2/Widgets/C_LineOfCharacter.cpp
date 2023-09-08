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
		break;
	case ECharacterLineType::PastMap_Start:
		PrintPastMap_1();
		break;
	case ECharacterLineType::HotelMap_Start:
		break;
	case ECharacterLineType::OpenEighthGuide:
		break;
	case ECharacterLineType::OpenNinthGuide:
		break;
	case ECharacterLineType::OpenTenthGuide:
		break;
	default:
		break;
	}
}

void UC_LineOfCharacter::ClearTextBlock()
{
	CharacterLineText->SetText(FText::FromString(""));
}

void UC_LineOfCharacter::PrintStartMap_1()
{
}

void UC_LineOfCharacter::PrintStartMap_2()
{
}

void UC_LineOfCharacter::PrintPastMap_1()
{
	CharacterLineText->SetText(PastMap_1);
	if (PlaySoundCharacterLine.IsBound())
		PlaySoundCharacterLine.Broadcast(ECharacterLineType::PastMap_Start);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UC_LineOfCharacter::ClearTextBlock, 3.5);
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

}

void UC_LineOfCharacter::PrintHotelMap_2()
{

}

void UC_LineOfCharacter::PrintEighthGuide()
{
	CharacterLineText->SetText(OpenEighthGuide);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UC_LineOfCharacter::ClearTextBlock, 5);
}

void UC_LineOfCharacter::PrintNinthGuide()
{
	// CharacterLineText->SetText(OpenEighthGuide);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UC_LineOfCharacter::ClearTextBlock, 5);
}

void UC_LineOfCharacter::PrintTenthGuide()
{
	// CharacterLineText->SetText(OpenEighthGuide);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UC_LineOfCharacter::ClearTextBlock, 5);
}

