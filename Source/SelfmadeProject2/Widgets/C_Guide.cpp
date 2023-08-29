#include "C_Guide.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Global.h"



bool UC_Guide::Initialize()
{
	bool bSuccess = Super::Initialize();
	CheckFalseResult(bSuccess, false);

	CheckNullResult(ForwardButton_1, false);
	ForwardButton_1->OnClicked.AddDynamic(this, &UC_Guide::ShowSecondPage);

	CheckNullResult(ForwardButton_2, false);
	ForwardButton_2->OnClicked.AddDynamic(this, &UC_Guide::ShowThirdPage);

	CheckNullResult(BackButton_2, false);
	BackButton_2->OnClicked.AddDynamic(this, &UC_Guide::ShowFirstPage);

	CheckNullResult(BackButton_3, false);
	BackButton_3->OnClicked.AddDynamic(this, &UC_Guide::ShowSecondPage);



	return true;
}

void UC_Guide::ShowFirstPage()
{
	CheckNull(GuidePageSwitcher);

	GuidePageSwitcher->SetActiveWidget(FirstPage);
}

void UC_Guide::ShowSecondPage()
{
	CheckNull(GuidePageSwitcher);

	GuidePageSwitcher->SetActiveWidget(SecondPage);
}

void UC_Guide::ShowThirdPage()
{
	CheckNull(GuidePageSwitcher);

	GuidePageSwitcher->SetActiveWidget(ThirdPage);
}

