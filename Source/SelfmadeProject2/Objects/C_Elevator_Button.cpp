#include "C_Elevator_Button.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Components/TextRenderComponent.h"
#include "Player/C_Player.h"
#include "Component/C_PlayerComponent.h"
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

	if (Floor == 1)
	{
		if (bInElevator == true)
			C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Material/ElevatorButtons/Instance/MAT_Number1_Inst");
		else
			C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Material/ElevatorButtons/Instance/MAT_Up_Inst");
	}
	else if (Floor == 2)
	{
		if (bInElevator)
			C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Material/ElevatorButtons/Instance/MAT_Number2_Inst");
		else if (bUpButton == true)
			C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Material/ElevatorButtons/Instance/MAT_Up_Inst");
		else
			C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Material/ElevatorButtons/Instance/MAT_Down_Inst");
	}
	else if (Floor == 3)
	{

		if (bInElevator)
			C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Material/ElevatorButtons/Instance/MAT_Number3_Inst");
		else if (bUpButton == true)
			C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Material/ElevatorButtons/Instance/MAT_Up_Inst");
		else
			C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Material/ElevatorButtons/Instance/MAT_Down_Inst");
	}
	else if (Floor == 4)
	{
		if (bInElevator)
			C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Material/ElevatorButtons/Instance/MAT_Number4_Inst");
		else if (bUpButton == true)
			C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Material/ElevatorButtons/Instance/MAT_Up_Inst");
		else
			C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Material/ElevatorButtons/Instance/MAT_Down_Inst");
	}
	else if (Floor == 5)
	{
		if (bInElevator)
			C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Material/ElevatorButtons/Instance/MAT_Number5_Inst");
		else
			C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Material/ElevatorButtons/Instance/MAT_Down_Inst");
	}

	else if (Floor == 0)
	{
		if (bOpenButton == true)
			C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Material/ElevatorButtons/Instance/MAT_Open_Inst");
		else
			C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Material/ElevatorButtons/Instance/MAT_Close_Inst");
	}

	DynamicMaterial = UMaterialInstanceDynamic::Create(DefaultMaterial, nullptr);
	ButtonMesh->SetMaterial(0, DynamicMaterial);
}

void AC_Elevator_Button::Tick(float DeltaTime)
{
	CheckFalse(bInElevator);

	Super::Tick(DeltaTime);

	FVector elevatorLocation = Elevator->GetActorLocation();

	if (Floor != 0)
	{
		FVector resultLocation = elevatorLocation + FVector(-132.f, -137.5f, (90.f + 20.f * Floor));

		if (Floor != 4) // Not ForthButtons
			SetActorLocation(resultLocation);

		else if (Player->PlayerComponent->DataAsset->OpenGuide.IsOpenTenth == true)
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
	CheckTrue((Elevator->bMoving == true) && (bIsInteraction == true));
	CheckFalse(Floor == 0 || bInElevator == false || Elevator->bCloseDoor == true);

	bIsInteraction = true;

	if (Floor != 0)
	{
		if (Elevator->MoveToFloor != Floor)
			Elevator->SetFloor(Floor);

		else if (PressOpenDoorButton.IsBound())
			PressOpenDoorButton.Broadcast(Floor);
	}
	else if ((bOpenButton == true) && (PressOpenDoorButton.IsBound()))
		PressOpenDoorButton.Broadcast(Floor);

	else if (PressCloseDoorButton.IsBound())
		PressCloseDoorButton.Broadcast(Floor);

	ChangeColor();
}