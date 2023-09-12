#include "C_RoomNum307.h"
#include "Components/BoxComponent.h"
#include "Player/C_Player.h"
#include "Widgets/C_Guide.h"
#include "Global.h"


AC_RoomNum307::AC_RoomNum307()
{
	C_Helpers::CreateSceneComponent(this, &Box, "Box");

	Box->bHiddenInGame = false; // For Test
}

void AC_RoomNum307::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AC_RoomNum307::OnBeginOverlap);
}

void AC_RoomNum307::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AC_Player* player = Cast<AC_Player>(OverlappedActor);
	player->CallLineOfCharacter(ECharacterLineType::OpenEighthGuide);
	player->GuideWidget->OpenEighthGuide();
}
