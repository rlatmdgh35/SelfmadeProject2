#include "C_LightSwitch.h"
#include "Components/PointLightComponent.h"
#include "Player/C_Player.h"
#include "Global.h"



AC_LightSwitch::AC_LightSwitch()
{
	C_Helpers::CreateSceneComponent(this, &DefaultSceneComponent, "DefaultSceneComponent");

	C_Helpers::CreateSceneComponent(this, &SwitchRoot, "SwitchRoot", DefaultSceneComponent);
	C_Helpers::CreateSceneComponent(this, &Switch, "Swtich", SwitchRoot);

	C_Helpers::CreateSceneComponent(this, &Plane1, "Plane1", DefaultSceneComponent);
	C_Helpers::CreateSceneComponent(this, &Plane2, "Plane2", DefaultSceneComponent);
	C_Helpers::CreateSceneComponent(this, &Plane3, "Plane3", DefaultSceneComponent);
	C_Helpers::CreateSceneComponent(this, &Plane4, "Plane4", DefaultSceneComponent);

	C_Helpers::CreateSceneComponent(this, &Light, "Light", DefaultSceneComponent);


	C_Helpers::GetAsset(&Cube, "/Game/StaticMeshes/SM_Cube");
	C_Helpers::GetAsset(&Material, "/Game/Materials/MAT_Basic");

	Switch->SetStaticMesh(Cube);
	Switch->SetMaterial(0, Material);
	Switch->SetRelativeLocationAndRotation(FVector(0, 2, -2), FRotator(0, 0, 45));
	Switch->SetRelativeScale3D(FVector(0.01f, 0.025f, 0.01f));

	Plane1->SetStaticMesh(Cube);
	Plane1->SetMaterial(0, Material);
	Plane1->SetRelativeLocation(FVector(-4, 0, 0));
	Plane1->SetRelativeScale3D(FVector(0.01f, 0.01f, 0.04f));

	Plane2->SetStaticMesh(Cube);
	Plane2->SetMaterial(0, Material);
	Plane2->SetRelativeLocation(FVector(4, 0, 0));
	Plane2->SetRelativeScale3D(FVector(0.01f, 0.01f, 0.04f));

	Plane3->SetStaticMesh(Cube);
	Plane3->SetMaterial(0, Material);
	Plane3->SetRelativeLocation(FVector(0, 0, 6));
	Plane3->SetRelativeScale3D(FVector(0.04125f, 0.01f, 0.01f));

	Plane4->SetStaticMesh(Cube);
	Plane4->SetMaterial(0, Material);
	Plane4->SetRelativeLocation(FVector(0, 0, -6));
	Plane4->SetRelativeScale3D(FVector(0.04125f, 0.01f, 0.01f));
}

void AC_LightSwitch::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> playerActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Player::StaticClass(), playerActor);
	Player = Cast<AC_Player>(playerActor[0]);

	ToggleLight(bIsOnLight);
}

void AC_LightSwitch::Interaction()
{
	ToggleLight(bIsOnLight);
}

void AC_LightSwitch::ToggleLight(bool IsOnLight)
{
	if (IsOnLight)
	{
		SwitchRoot->SetRelativeRotation(FRotator(0, 0, 270));
		Light->SetVisibility(true);
		bIsOnLight = false;
	}
	else
	{
		SwitchRoot->SetRelativeRotation(FRotator(0, 0, 0));
		Light->SetVisibility(false);
		bIsOnLight = true;
	}


}