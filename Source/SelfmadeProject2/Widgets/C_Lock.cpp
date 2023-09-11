#include "C_Lock.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "GameFramework/Character.h"
#include "Player/C_Player.h"
#include "Global.h"


bool UC_Lock::Initialize()
{
	Super::Initialize();

	QuitButton->OnClicked.AddDynamic(this, &UC_Lock::Quit);

	return true;
}

void UC_Lock::BeginPlay(ACharacter* InCharacter)
{
	Player = Cast<AC_Player>(InCharacter);
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
			Quit();

			if (OpenTenthGuide.IsBound())
				OpenTenthGuide.Broadcast();
		}

		else
		{
			ClearNum();
			Index = 1;
		}
	}
}

void UC_Lock::PressBackSpace()
{
	if (Index == 2)
	{
		FirstNum->SetText(FText::FromString("-"));
		Index--;
	}
	else if (Index == 3)
	{
		SecondNum->SetText(FText::FromString("-"));
		Index--;
	}
	else if (Index == 4)
	{
		ThirdNum->SetText(FText::FromString("-"));
		Index--;
	}
}

bool UC_Lock::CheckLockNum()
{
	if (
		(FirstNum->GetText().ToString()		== "7") && 
		(SecondNum->GetText().ToString()	== "3") && 
		(ThirdNum->GetText().ToString()		== "0") && 
		(ForthNum->GetText().ToString()		== "9")
		)
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

void UC_Lock::Quit()
{
	APlayerController* controller = Cast<APlayerController>(Player->GetController());
	controller->bShowMouseCursor = false;

	Player->InteractionType = EInteractionType::None;
	Player->bStopLocation = false;
	Player->bStopRotation = false;
	Player->LockWidget->SetVisibility(ESlateVisibility::Hidden);
}