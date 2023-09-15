#include "C_StartMapGameMode.h"
#include "Player/C_Player.h"
#include "Global.h"


AC_StartMapGameMode::AC_StartMapGameMode()
{
	TSubclassOf<AC_Player> player;
	C_Helpers::GetClass(&player, "/Game/Player/Blueprint/BP_Player");
	DefaultPawnClass = player;
}

void AC_StartMapGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> playerActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Player::StaticClass(), playerActor);
	AC_Player* player = Cast<AC_Player>(playerActor[0]);
	player->CallChangeMap(ECurrentMap::Start);
}