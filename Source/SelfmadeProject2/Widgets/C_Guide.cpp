#include "C_Guide.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "GameFramework/Character.h"
#include "Player/C_Player.h"
#include "Components/C_PlayerComponent.h"
#include "DataAsset/C_DataAsset.h"
#include "Collisions/C_RoomNum307.h"
#include "Collisions/C_RoomNum508.h"
#include "Widgets/C_Lock.h"
#include "Widgets/C_LineOfCharacter.h" // 
#include "Global.h"



void UC_Guide::BeginPlay(ACharacter* InCharacter)
{
	Player = Cast<AC_Player>(InCharacter);

	TArray<AActor*> roomNum307Actor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_RoomNum307::StaticClass(), roomNum307Actor);
	if (roomNum307Actor.Num() > 0)
	{
		RoomNum307 = Cast<AC_RoomNum307>(roomNum307Actor[0]);
		RoomNum307->OpenEighthGuide.AddDynamic(this, &UC_Guide::OpenEighthGuide);
	}

	TArray<AActor*> roomNum508Actor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_RoomNum508::StaticClass(), roomNum508Actor);
	if (roomNum508Actor.Num() > 0)
	{
		RoomNum508 = Cast<AC_RoomNum508>(roomNum508Actor[0]);
		RoomNum508->OpenNinthGuide.AddDynamic(this, &UC_Guide::OpenNinthGuide);
	}

	LockWidget = Cast<UC_Lock>(Player->LockWidget);
	LockWidget->OpenTenthGuide.AddDynamic(this, &UC_Guide::OpenTenthGuide);
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
	Player->PlayerComponent->DataAsset->OpenGuide.IsOpenEighth = true;
	Player->CallLineOfCharacter(ECharacterLineType::OpenEighthGuide);

	if (Player->PlayerComponent->DataAsset->OpenGuide.IsOpenTenth == true)
	{
		if (Player->PlayerComponent->DataAsset->OpenGuide.IsOpenNinth == true)
		{
			Mosaic->SetText(FText::FromString(
				EighthText.ToString() + 
				NinthText.ToString() + 
				TenthText.ToString()
			));	
		}
		else
		{
			Mosaic->SetText(FText::FromString(
				EighthText.ToString() +
				MosaicNinthText.ToString() +
				TenthText.ToString()
			));
		}
	}
	else
	{
		if (Player->PlayerComponent->DataAsset->OpenGuide.IsOpenNinth == true)
		{
			Mosaic->SetText(FText::FromString(
				EighthText.ToString() + 
				NinthText.ToString()
			));
		}
		else
		{
			Mosaic->SetText(FText::FromString(
				EighthText.ToString() +
				MosaicNinthText.ToString()
			));
		}
	}
}

void UC_Guide::OpenNinthGuide()
{
	Player->PlayerComponent->DataAsset->OpenGuide.IsOpenNinth = true;
	Player->CallLineOfCharacter(ECharacterLineType::OpenNinthGuide);

	if (Player->PlayerComponent->DataAsset->OpenGuide.IsOpenTenth == true)
	{
		if (Player->PlayerComponent->DataAsset->OpenGuide.IsOpenEighth == true)
		{
			Mosaic->SetText(FText::FromString(
				EighthText.ToString() + 
				NinthText.ToString() + 
				TenthText.ToString()
			));
		}
		else
		{
			Mosaic->SetText(FText::FromString(
				MosaicEighthText.ToString() +
				NinthText.ToString() +
				TenthText.ToString()
			));
		}
	}
	else
	{
		if (Player->PlayerComponent->DataAsset->OpenGuide.IsOpenEighth== true)
		{
			Mosaic->SetText(FText::FromString(
				EighthText.ToString() +
				NinthText.ToString()
			));
		}
		else
		{
			Mosaic->SetText(FText::FromString(
				MosaicEighthText.ToString() +
				NinthText.ToString()
			));
		}
	}

}

void UC_Guide::OpenTenthGuide()
{
	Player->PlayerComponent->DataAsset->OpenGuide.IsOpenTenth = true;
	Player->CallLineOfCharacter(ECharacterLineType::OpenTenthGuide);

	if (Player->PlayerComponent->DataAsset->OpenGuide.IsOpenNinth == true)
	{
		if (Player->PlayerComponent->DataAsset->OpenGuide.IsOpenEighth == true)
		{
			Mosaic->SetText(FText::FromString(
				EighthText.ToString() +
				NinthText.ToString() + 
				TenthText.ToString()
			));
		}
		else
		{
			Mosaic->SetText(FText::FromString(
				MosaicEighthText.ToString() +
				NinthText.ToString() +
				TenthText.ToString()
			));
		}
	}
	else
	{
		if (Player->PlayerComponent->DataAsset->OpenGuide.IsOpenEighth == true)
		{
			Mosaic->SetText(FText::FromString(
				EighthText.ToString() +
				MosaicNinthText.ToString() +
				TenthText.ToString()
			));
		}
		else
		{
			Mosaic->SetText(FText::FromString(
				MosaicEighthText.ToString() +
				MosaicNinthText.ToString() +
				TenthText.ToString()
			));
		}
	}
}
