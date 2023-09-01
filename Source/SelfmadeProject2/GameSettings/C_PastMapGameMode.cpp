#include "C_PastMapGameMode.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/C_Player.h"
#include "DataAsset/C_DataAsset.h"
#include "Global.h"

AC_PastMapGameMode::AC_PastMapGameMode()
{
	TSubclassOf<AC_Player> player;
	C_Helpers::GetClass(&player, "/Game/Player/BluePrint/BP_Player");

	DefaultPawnClass = player;
}

void AC_PastMapGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> playerActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Player::StaticClass(), playerActor);
	AC_Player* player = Cast<AC_Player>(playerActor[0]);
	
	player->CurrentMap = ECurrentMap::Past;
	player->GetCharacterMovement()->MaxWalkSpeed = 600.f;
	player->SetActorLocation(FVector(4775, 3150, 120));
}
