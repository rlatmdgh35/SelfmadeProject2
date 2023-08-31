#include "C_Lock.h"
#include "Components/TextBlock.h"
#include "GameFramework/Character.h"
#include "Player/C_Player.h"
#include "DataAsset/C_DataAsset.h"
#include "Global.h"


void UC_Lock::BeginPlay(ACharacter* InCharacter)
{
	C_Log::Print(InCharacter->GetName());
	// Player = Cast<AC_Player>(InCharacter);
}

void UC_Lock::SetTextNum(FText InText)
{
	if (Index == 1)
	{
		FirstNum->SetText(InText);
		Index++;
	}
	else if (Index == 2)
	{
		SecondNum->SetText(InText);
		Index++;
	}
	else if(Index == 3)
	{
		ThirdNum->SetText(InText);
		Index++;
	}
	else
	{
		ForthNum->SetText(InText);

		if (CheckLockNum())
		{
			Player->DataAsset->OpenGuide.IsOpenTenth = true;
			Index = 1;
			C_Log::Print("True");
		}

		else
		{
			ClearNum();
			Index = 1;
			C_Log::Print("False");
		}
	}
}

void UC_Lock::PressBackSpace()
{
	if (Index == 1)
	{
		FirstNum->SetText(FText::FromString(""));
	}
	else if (Index == 2)
	{
		SecondNum->SetText(FText::FromString(""));
		Index--;
	}
	else if (Index == 3)
	{
		ThirdNum->SetText(FText::FromString(""));
		Index--;
	}
}

bool UC_Lock::CheckLockNum()
{
	if ((FirstNum->GetText().ToString() == "7") && (SecondNum->GetText().ToString() == "3") && (ThirdNum->GetText().ToString() == "0") && (ForthNum->GetText().ToString() == "9"))
		return true;

	return false;
}

void UC_Lock::ClearNum()
{
	FirstNum->SetText(FText::FromString("-"));
	SecondNum->SetText(FText::FromString("-"));
	ThirdNum->SetText(FText::FromString("-"));
	ForthNum->SetText(FText::FromString("-"));
}

