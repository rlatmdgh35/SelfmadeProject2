#include "C_PastMapGameMode.h"
#include "Player/C_Player.h"
#include "Global.h"


AC_PastMapGameMode::AC_PastMapGameMode()
{
	TSubclassOf<AC_Player> player;
	C_Helpers::GetClass(&player, "/Game/Player/Blueprint/BP_Player");
	DefaultPawnClass = player;
}

void AC_PastMapGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> playerActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Player::StaticClass(), playerActor);
	AC_Player* player = Cast<AC_Player>(playerActor[0]);
	player->CallChangeMap(ECurrentMap::Past);
}
