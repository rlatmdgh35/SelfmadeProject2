#include "C_LineOfCharacter.h"
#include "Components/TextBlock.h"
#include "GameFramework/Character.h"
#include "Player/C_Player.h"
#include "Global.h"



void UC_LineOfCharacter::BeginPlay(ACharacter* InCharacter)
{
	AC_Player* player = Cast<AC_Player>(InCharacter);

	player->CharacterLineType.AddDynamic(this, &UC_LineOfCharacter::SetCharacterLine);
}


void UC_LineOfCharacter::SetCharacterLine(ECharacterLineType InType)
{

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

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UC_LineOfCharacter::PrintPastMap_2, 3);
}

void UC_LineOfCharacter::PrintPastMap_2()
{
	CharacterLineText->SetText(PastMap_2);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UC_LineOfCharacter::PrintPastMap_3, 3);
}

void UC_LineOfCharacter::PrintPastMap_3()
{
	CharacterLineText->SetText(PastMap_3);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UC_LineOfCharacter::ClearTextBlock, 3);
}

void UC_LineOfCharacter::PrintPastMap_4()
{
}

void UC_LineOfCharacter::PrintPastMap_5()
{
	if (PastMapSetOffLoop.IsBound())
		PastMapSetOffLoop.Broadcast();
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

