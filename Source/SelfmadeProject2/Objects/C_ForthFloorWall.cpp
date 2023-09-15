#include "C_ForthFloorWall.h"
#include "Player/C_Player.h"
#include "Widgets/C_Lock.h"
#include "Global.h"


AC_ForthFloorWall::AC_ForthFloorWall()
{
	C_Helpers::CreateSceneComponent(this, &Wall, "Wall");

	PrimaryActorTick.bCanEverTick = true;
}

void AC_ForthFloorWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Player == nullptr)
	{
		TArray<AActor*> playerActor;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Player::StaticClass(), playerActor);
		Player = Cast<AC_Player>(playerActor[0]);
		if (Player != nullptr)
			Player->LockWidget->OpenTenthGuide.AddDynamic(this, &AC_ForthFloorWall::DeleteActor);
	}
}

void AC_ForthFloorWall::DeleteActor()
{
	Destroy();
}
