#include "C_HotelMapGameMode.h"
#include "Player/C_Player.h"
#include "Global.h"


AC_HotelMapGameMode::AC_HotelMapGameMode()
{
	TSubclassOf<AC_Player> player;
	C_Helpers::GetClass(&player, "Blueprint'/Game/Player/Blueprint/BP_Player.BP_Player_C'");
	DefaultPawnClass = player;
}

void AC_HotelMapGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> playerActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Player::StaticClass(), playerActor);
	AC_Player* player = Cast<AC_Player>(playerActor[0]);
	player->CallChangeMap(ECurrentMap::Hotel);
}