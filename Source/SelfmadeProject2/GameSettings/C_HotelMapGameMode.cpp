#include "C_HotelMapGameMode.h"
#include "Player/C_Player.h"
#include "Global.h"



AC_HotelMapGameMode::AC_HotelMapGameMode()
{
	C_Helpers::GetAsset(&SkeletalMesh, "/Game/Character/Past/Mesh/Ch18_nonPBR");
	C_Helpers::GetClass(&AnimClass, "/Game/Player/Blueprint/ABP_Player_Past");

	TSubclassOf<AC_Player> player;
	C_Helpers::GetClass(&player, "/Game/Player/Blueprint/BP_Player");
	DefaultPawnClass = player;
}

void AC_HotelMapGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> playerActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Player::StaticClass(), playerActor);
	AC_Player* player = Cast<AC_Player>(playerActor[0]);

	player->GetMesh()->SetSkeletalMesh(SkeletalMesh);
	player->GetMesh()->SetAnimInstanceClass(AnimClass);
	player->CurrentMap = ECurrentMap::Hotel;
}