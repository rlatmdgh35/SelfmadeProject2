#include "C_Elevator_Button.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Components/TextRenderComponent.h"
#include "Player/C_Player.h"

#include "DataAsset/C_DataAsset.h"
#include "Global.h"


AC_Elevator_Button::AC_Elevator_Button()
{
	PrimaryActorTick.bCanEverTick = true;

	C_Helpers::CreateSceneComponent<UStaticMeshComponent>(this, &ButtonMesh, "Button", RootSceneComponent);

	UStaticMesh* cubeMesh;
	C_Helpers::GetAsset(&cubeMesh, "StaticMesh'/Game/StaticMeshes/SM_Cube.SM_Cube'");

	ButtonMesh->SetStaticMesh(cubeMesh);
	ButtonMesh->SetRelativeScale3D(FVector(0.02f, 0.04f, 0.04f));

	Text->SetVisibility(false);
}

void AC_Elevator_Button::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> elevatorActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Elevator::StaticClass(), elevatorActor);
	for (int32 i = 0; i < elevatorActor.Num(); i++) // Do Not Need for (Only SpawnWorld In HotelMap both)
	{
		if (elevatorActor[i]->Tags.Num() > 0)
		{
			if (elevatorActor[i]->Tags[0] == FName("Elevator"))
				Elevator = Cast<AC_Elevator>(elevatorActor[i]);
		}
	}

	if (bInElevator != true)
		SetActorRelativeRotation(FRotator(0, 180, 0));

	if (bInElevator == true)
	{
		switch (Floor)
		{
		case EMoveToFloor::First:		C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Materials/ElevatorButtons/Instance/MAT_Number1_Inst");	break;
		case EMoveToFloor::Second:		C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Materials/ElevatorButtons/Instance/MAT_Number2_Inst");	break;
		case EMoveToFloor::Third:		C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Materials/ElevatorButtons/Instance/MAT_Number3_Inst");	break;
		case EMoveToFloor::Forth:		C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Materials/ElevatorButtons/Instance/MAT_Number4_Inst");	break;
		case EMoveToFloor::Fifth:		C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Materials/ElevatorButtons/Instance/MAT_Number5_Inst");	break;
		case EMoveToFloor::Arrow:	
			if (bOpenButton == true)	C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Materials/ElevatorButtons/Instance/MAT_Open_Inst");
			else						C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Materials/ElevatorButtons/Instance/MAT_Close_Inst");

			break;
		}
	}
	else if (bUpButton == true)
	{
		switch (Floor)
		{
		case EMoveToFloor::First:		C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Materials/ElevatorButtons/Instance/MAT_Up_Inst");		break;
		case EMoveToFloor::Second:		C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Materials/ElevatorButtons/Instance/MAT_Up_Inst");		break;
		case EMoveToFloor::Third:		C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Materials/ElevatorButtons/Instance/MAT_Up_Inst");		break;
		case EMoveToFloor::Forth:		C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Materials/ElevatorButtons/Instance/MAT_Up_Inst");		break;
		}
	}
	else
	{
		switch (Floor)
		{
		case EMoveToFloor::Second:		C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Materials/ElevatorButtons/Instance/MAT_Down_Inst");		break;
		case EMoveToFloor::Third:		C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Materials/ElevatorButtons/Instance/MAT_Down_Inst");		break;
		case EMoveToFloor::Forth:		C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Materials/ElevatorButtons/Instance/MAT_Down_Inst");		break;
		case EMoveToFloor::Fifth:		C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Materials/ElevatorButtons/Instance/MAT_Down_Inst");		break;
		}
	}


	DynamicMaterial = UMaterialInstanceDynamic::Create(DefaultMaterial, nullptr);
	ButtonMesh->SetMaterial(0, DynamicMaterial);
}

void AC_Elevator_Button::Tick(float DeltaTime)
{
	CheckFalse(bInElevator);

	Super::Tick(DeltaTime);

	FVector elevatorLocation = Elevator->GetActorLocation();

	if (Floor != EMoveToFloor::Arrow)
	{
		FVector resultLocation = elevatorLocation + FVector(-132.f, -137.5f, (90.f + 20.f * (int32)Floor));

		if (Floor != EMoveToFloor::Forth) // Not ForthButtons
			SetActorLocation(resultLocation);

		else if (Player->DataAsset->OpenGuide.IsOpenTenth == true)
			SetActorLocation(resultLocation);
	}
	else
	{
		FVector resultLocation = elevatorLocation + FVector(-132, (-150 + 25 * bOpenButton), 90);	// If bOpenButton == true -> SetLocation(-132, -125, 90)
																									// If bOpenButton == false -> SetLocation(-132, -150, 90);
		SetActorLocation(resultLocation);
	}
}

void AC_Elevator_Button::Interaction()
{
	CheckTrue(Elevator->bMoving == true);
	CheckFalse(Floor == EMoveToFloor::Arrow || bInElevator == false ||Elevator->bCloseDoor == true);

	bIsInteraction = true;

	if (Floor != EMoveToFloor::Arrow)
	{
		if (Elevator->MoveToFloor != Floor)
		{
			Player->InteractionType = EInteractionType::Elevator;
			Elevator->SetFloor(Floor);
		}

		else if (PressOpenDoorButton.IsBound())
		{
			Player->InteractionType = EInteractionType::Elevator;
			PressOpenDoorButton.Broadcast(Floor);
		}
	}
	else if ((bOpenButton == true) && (PressOpenDoorButton.IsBound()))
		PressOpenDoorButton.Broadcast(Floor);

	else if (PressCloseDoorButton.IsBound())
		PressCloseDoorButton.Broadcast(Floor);
}