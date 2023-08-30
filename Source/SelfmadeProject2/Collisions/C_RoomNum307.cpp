#include "C_RoomNum307.h"
#include "Components/BoxComponent.h"
#include "Player/C_Player.h"
#include "DataAsset/C_DataAsset.h"
#include "Global.h"


AC_RoomNum307::AC_RoomNum307()
{
	C_Helpers::CreateSceneComponent(this, &Box, "Box");

	Box->bHiddenInGame = false;
}

void AC_RoomNum307::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AC_RoomNum307::OnBeginOverlap);
}

void AC_RoomNum307::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Player = Cast<AC_Player>(OtherActor);
	CheckNull(Player);

	C_Log::Print("Overlapped");
	Player->DataAsset->OpenGuide.IsOpenEighth = true;

	Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (OpenEighthGuide.IsBound())
		OpenEighthGuide.Broadcast();
}

