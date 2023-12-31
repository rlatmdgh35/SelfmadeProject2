#include "C_RoomNum508.h"
#include "Components/BoxComponent.h"
#include "Player/C_Player.h"
#include "Widgets/C_Guide.h"
#include "Global.h"


AC_RoomNum508::AC_RoomNum508()
{
	C_Helpers::CreateSceneComponent(this, &Box, "Box");

	Box->bHiddenInGame = false;
}

void AC_RoomNum508::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AC_RoomNum508::OnBeginOverlap);
}

void AC_RoomNum508::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AC_Player* player = Cast<AC_Player>(OverlappedActor);
	player->CallLineOfCharacter(ECharacterLineType::OpenNinthGuide);
	player->GuideWidget->OpenNinthGuide();
}
