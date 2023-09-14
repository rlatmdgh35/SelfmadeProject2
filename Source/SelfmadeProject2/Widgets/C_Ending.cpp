#include "C_Ending.h"
#include "Components/WidgetSwitcher.h"



void UC_Ending::EndingType(EEndingType InType)
{
	switch (InType)
	{
	case EEndingType::Sad:
		EndingSwitch->SetActiveWidget(SadEnding);
		break;
	case EEndingType::Normal:
		EndingSwitch->SetActiveWidget(NormalEnding);
		break;
	case EEndingType::Happy:
		EndingSwitch->SetActiveWidget(HappyEnding);
		break;
	case EEndingType::Hidden:
		EndingSwitch->SetActiveWidget(HiddenEnding);
		break;
	}
}