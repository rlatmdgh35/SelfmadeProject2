#include "C_Guide.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "Components/Widget.h"
#include "GameFramework/Character.h"
#include "Player/C_Player.h"
#include "DataAsset/C_DataAsset.h"
#include "Collisions/C_RoomNum307.h"
#include "Collisions/C_RoomNum508.h"
#include "Widgets/C_Lock.h"
#include "Global.h"



void UC_Guide::BeginPlay(ACharacter* InCharacter, UWidget* InWidget)
{
	Player = Cast<AC_Player>(InCharacter);

	TArray<AActor*> roomNum307Actor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_RoomNum307::StaticClass(), roomNum307Actor);
	if (roomNum307Actor.Num() > 0)
	{
		RoomNum307 = Cast<AC_RoomNum307>(roomNum307Actor[0]);
		// RoomNum307->OpenEighthGuide.AddDynamic(this, &UC_Guide::OpenEighthGuide);
	}

	TArray<AActor*> roomNum508Actor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_RoomNum508::StaticClass(), roomNum508Actor);
	if (roomNum508Actor.Num() > 0)
	{
		RoomNum508 = Cast<AC_RoomNum508>(roomNum508Actor[0]);
		// RoomNum508->OpenNinthGuide.AddDynamic(this, &UC_Guide::OpenNinthGuide);
	}

	LockWidget = Cast<UC_Lock>(InWidget);
	// LockWidget->OpenTenthGuide.AddDynamic(this, &UC_Guide::OpenTenthGuide);
}

bool UC_Guide::Initialize()
{
	Super::Initialize();

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

/*
void UC_Guide::OpenEighthGuide()
{
	Player->DataAsset->OpenGuide.IsOpenEighth = true;

	Mosaic->SetText(FText::FromString(""));
	if (Player->DataAsset->OpenGuide.IsOpenTenth == true)
	{
		if (Player->DataAsset->OpenGuide.IsOpenNinth == true)
		{
			Mosaic->SetText(FText::FromString(
			EighthText + NinthText + TenthText
			));	
		}
		else
		{
			Mosaic->SetText(FText::FromString(
				EighthText +
				MosaicNinthText +
				TenthText
			));
		}
	}
	else
	{
		if (Player->DataAsset->OpenGuide.IsOpenNinth == true)
		{
			Mosaic->SetText(FText::FromString(
				EighthText + NinthText
			));
		}
		else
		{
			Mosaic->SetText(FText::FromString(
				EighthText +
				MosaicNinthText
			));
		}
	}
}

void UC_Guide::OpenNinthGuide()
{
	Player->DataAsset->OpenGuide.IsOpenNinth = true;
	
	Mosaic->SetText(FText::FromString(""));
	if (Player->DataAsset->OpenGuide.IsOpenTenth == true)
	{
		if (Player->DataAsset->OpenGuide.IsOpenEighth == true)
		{
			Mosaic->SetText(FText::FromString(
				EighthText + NinthText + TenthText
			));
		}
		else
		{
			Mosaic->SetText(FText::FromString(
				MosaicEighthText +
				NinthText +
				TenthText
			));
		}
	}
	else
	{
		if (Player->DataAsset->OpenGuide.IsOpenEighth== true)
		{
			Mosaic->SetText(FText::FromString(
				EighthText + NinthText
			));
		}
		else
		{
			Mosaic->SetText(FText::FromString(
				MosaicEighthText +
				NinthText
			));
		}
	}

}

void UC_Guide::OpenTenthGuide()
{
	Player->DataAsset->OpenGuide.IsOpenTenth = true;

	if (Player->DataAsset->OpenGuide.IsOpenNinth == true)
	{
		if (Player->DataAsset->OpenGuide.IsOpenEighth == true)
		{
			Mosaic->SetText(FText::FromString(
				EighthText + NinthText + TenthText
			));
		}
		else
		{
			Mosaic->SetText(FText::FromString(
				MosaicEighthText +
				NinthText +
				TenthText
			));
		}
	}
	else
	{
		if (Player->DataAsset->OpenGuide.IsOpenEighth == true)
		{
			Mosaic->SetText(FText::FromString(
				EighthText + 
				MosaicNinthText + 
				TenthText
			));
		}
		else
		{
			Mosaic->SetText(FText::FromString(
				MosaicEighthText +
				MosaicNinthText + 
				TenthText
			));
		}
	}
}
*/