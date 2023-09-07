#include "C_Elevator.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Player/C_Player.h"
#include "Component/C_PlayerComponent.h"
#include "DataAsset/C_DataAsset.h"
#include "C_Elevator_Button.h"
#include "Global.h"



AC_Elevator::AC_Elevator()
{
	PrimaryActorTick.bCanEverTick = true;

	C_Helpers::CreateSceneComponent<USceneComponent>(this, &RootSceneComponent, "RootSceneComponent");
	C_Helpers::CreateSceneComponent<UStaticMeshComponent>(this, &TopMesh, "TopMesh", RootComponent);
	C_Helpers::CreateSceneComponent<UTextRenderComponent>(this, &Text, "Text", TopMesh);

	TopMesh->SetRelativeLocation(FVector(-152, 0, 267));
	TopMesh->SetRelativeScale3D(FVector(0.1375f, 0.8f, 0.25f));
	Text->SetRelativeLocation(FVector(130, 0, 0));
	Text->SetRelativeScale3D(FVector(1.f, 1.5f, 5.f));
}

void AC_Elevator::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> buttonActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Elevator_Button::StaticClass(), buttonActors);
	
	for (int32 i = 0; i < buttonActors.Num(); i++)
	{
		Buttons.Add(Cast<AC_Elevator_Button>(buttonActors[i]));
		Buttons[i]->PressOpenDoorButton.AddDynamic(this, &AC_Elevator::DoMoveDoor);
		Buttons[i]->PressCloseDoorButton.AddDynamic(this, &AC_Elevator::CloseDoor);
	}

	TArray<AActor*> playerActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Player::StaticClass(), playerActor);
	Player = Cast<AC_Player>(playerActor[0]);
}

void AC_Elevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float zLocation = GetActorLocation().Z;
	if (50.f <= zLocation && zLocation < 300.f)				Text->SetText(FText::FromString("1"));
	else if (300.f <= zLocation && zLocation < 800.f)		Text->SetText(FText::FromString("2"));
	else if (800.f <= zLocation && zLocation < 1300.f)		Text->SetText(FText::FromString("3"));
	else if (1300.f <= zLocation && zLocation < 1800.f)
	{
		CheckFalse(Player->PlayerComponent->DataAsset->OpenGuide.IsOpenTenth == true);
		Text->SetText(FText::FromString("4"));
		Text->SetTextRenderColor(FColor::Red);
	}
	else if (1800.f <= zLocation && zLocation <= 2050.f)	Text->SetText(FText::FromString("5"));
}

void AC_Elevator::SetFloor(int32 InFloor)
{
	StartLocation = GetActorLocation();
	MoveToFloor = InFloor;
	bMoving = true;

	C_Log::Print("Set Floor, Move To Floor : " + FString::FromInt(MoveToFloor));
}

void AC_Elevator::ChangeColor()
{
	// Todo. Change Move To Floor Type

	C_Log::Print("Color, Move To Floor : " + FString::FromInt(MoveToFloor));

	for (int32 i = 0; i < Buttons.Num(); i++)
	{
		if (Buttons[i]->bIsInteraction == true)
		{
			if (Buttons[i]->Floor == 0 ||
				Buttons[i]->Floor == MoveToFloor)
			{
				Buttons[i]->DynamicMaterial->SetVectorParameterValue("Param", FLinearColor(1, 0, 0));

				FTimerHandle timerhandle;
				GetWorldTimerManager().SetTimer(timerhandle, this, &AC_Elevator::ResetButtonColor, 1);
				break;
			}
			else
			{
				Buttons[i]->DynamicMaterial->SetVectorParameterValue("Param", FLinearColor(1, 0, 0));
				break;
			}
		}
	}
}

void AC_Elevator::ResetButtonColor()
{
	for (int32 i = 0; i < Buttons.Num(); i++)
	{
		if (Buttons[i]->bIsInteraction == true)
		{
			Buttons[i]->DynamicMaterial->SetVectorParameterValue("Param", FLinearColor(0, 1, 0));
			Buttons[i]->bIsInteraction = false;
			break;
		}
	}
}