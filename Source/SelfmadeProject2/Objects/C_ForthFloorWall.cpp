#include "C_ForthFloorWall.h"
#include "Player/C_Player.h"
#include "Widgets/C_Lock.h"
#include "Global.h"


AC_ForthFloorWall::AC_ForthFloorWall()
{
	C_Helpers::CreateSceneComponent(this, &Wall, "Wall");
}

void AC_ForthFloorWall::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> playerActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Player::StaticClass(), playerActors);
	AC_Player* player = Cast<AC_Player>(playerActors[0]);
	player->LockWidget->OpenTenthGuide.AddDynamic(this, &AC_ForthFloorWall::DeleteActor);
}

void AC_ForthFloorWall::DeleteActor()
{
	Destroy();
}
