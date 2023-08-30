#include "C_Guide.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "Collisions/C_RoomNum307.h"
#include "Collisions/C_RoomNum508.h"
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



	/*
	RoomNum307->OpenEighthGuide.AddDynamic(this, &UC_Guide::OpenEighthGuide);
	RoomNum508->OpenNinthGuide.AddDynamic(this, &UC_Guide::OpenNinthGuide);
	*/

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

void UC_Guide::OpenEighthGuide()
{
	
}

void UC_Guide::OpenNinthGuide()
{


}
