#include "C_Elevator_Button.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Player/C_Player.h"
#include "Component/C_PlayerComponent.h"
#include "DataAsset/C_DataAsset.h"
#include "Global.h"


AC_Elevator_Button::AC_Elevator_Button()
{
	PrimaryActorTick.bCanEverTick = true;

	C_Helpers::CreateSceneComponent<UStaticMeshComponent>(this, &ButtonMesh, "Button", RootComponent);

	UStaticMesh* cubeMesh;
	C_Helpers::GetAsset(&cubeMesh, "StaticMesh'/Game/StaticMeshes/SM_Cube.SM_Cube'");

	ButtonMesh->SetStaticMesh(cubeMesh);
	ButtonMesh->SetRelativeScale3D(FVector(0.02f, 0.04f, 0.04f));
}

void AC_Elevator_Button::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> elevatorActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Elevator::StaticClass(), elevatorActor);
	for (uint8 i = 0; i < elevatorActor.Num(); i++)
	{
		if (elevatorActor[i]->Tags.Num() > 0)
		{
			if (elevatorActor[i]->Tags[0] == FName("Elevator"))
				Elevator = Cast<AC_Elevator>(elevatorActor[i]);
		}
	}

	if (bInElevator != true)
		SetActorRelativeRotation(FRotator(0, 180, 0));

	switch (Floor)
	{
	case EMoveToFloor::First:
		if (bInElevator == true)
			C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Material/ElevatorButtons/Instance/MAT_Number1_Inst");
		else
			C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Material/ElevatorButtons/Instance/MAT_Up_Inst");
		
		break;

	case EMoveToFloor::Second:
		if (bInElevator)
			C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Material/ElevatorButtons/Instance/MAT_Number2_Inst");
		else if (bUpButton == true)
			C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Material/ElevatorButtons/Instance/MAT_Up_Inst");
		else
			C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Material/ElevatorButtons/Instance/MAT_Down_Inst");

		break;

	case EMoveToFloor::Third:
		if (bInElevator)
			C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Material/ElevatorButtons/Instance/MAT_Number3_Inst");
		else if (bUpButton == true)
			C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Material/ElevatorButtons/Instance/MAT_Up_Inst");
		else
			C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Material/ElevatorButtons/Instance/MAT_Down_Inst");

		break;

	case EMoveToFloor::Forth:
		if (bInElevator)
			C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Material/ElevatorButtons/Instance/MAT_Number4_Inst");
		else if (bUpButton == true)
			C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Material/ElevatorButtons/Instance/MAT_Up_Inst");
		else
			C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Material/ElevatorButtons/Instance/MAT_Down_Inst");

		break;

	case EMoveToFloor::Fifth:
		if (bInElevator)
			C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Material/ElevatorButtons/Instance/MAT_Number5_Inst");
		else
			C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Material/ElevatorButtons/Instance/MAT_Down_Inst");

		break;

	case EMoveToFloor::Arrow:
		if (bOpenButton == true)
			C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Material/ElevatorButtons/Instance/MAT_Open_Inst");
		else
			C_Helpers::AssetDynamic<UMaterialInstanceConstant>(&DefaultMaterial, "/Game/Material/ElevatorButtons/Instance/MAT_Close_Inst");
		break;
	}

	DynamicMaterial = UMaterialInstanceDynamic::Create(DefaultMaterial, nullptr);
	ButtonMesh->SetMaterial(0, DynamicMaterial);

	TArray<AActor*> playerActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Player::StaticClass(), playerActor);
	Player = Cast<AC_Player>(playerActor[0]);
}

void AC_Elevator_Button::Tick(float DeltaTime)
{
	CheckFalse(bInElevator);

	Super::Tick(DeltaTime);

	FVector elevatorLocation = Elevator->GetActorLocation();

	if (Floor != EMoveToFloor::Arrow)
	{
		FVector resultLocation = elevatorLocation + FVector(-132.f, -137.5f, (110.f + 20.f * (float)Floor));

		if ((float)Floor != 3) // Not ForthButtons
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
	CheckFalse(Floor == EMoveToFloor::Arrow || bInElevator == false || Elevator->bCloseDoor == true);

	bIsInteraction = true;

	ChangeColor();

	if (Floor != EMoveToFloor::Arrow)
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
}