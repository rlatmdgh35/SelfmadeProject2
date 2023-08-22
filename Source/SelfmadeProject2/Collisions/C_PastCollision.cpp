#include "C_PastCollision.h"
#include "Components/BoxComponent.h"
#include "Player/C_Player.h"
#include "Global.h"


AC_PastCollision::AC_PastCollision()
{
	C_Helpers::CreateSceneComponent(this, &Box, "Box");
	Box->SetRelativeScale3D(FVector(15, 3, 5));
}

void AC_PastCollision::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AC_PastCollision::BeginOverlap);
}

void AC_PastCollision::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AC_PastCollision::TravelHotel, 5);

}

void AC_PastCollision::TravelHotel()
{
	UWorld* world = GetWorld();
	CheckNull(world);

	world->ServerTravel("/Game/Maps/HotelMap");

	// USkeletalMesh* skeletalMesh;
	// C_Helpers::GetAsset(&skeletalMesh, "/Game/Character/Past/Mesh/Ch18_nonPBR");
	// 
	// 
	// TSubclassOf<AC_Player> playerClass;
	// C_Helpers::GetClass(&playerClass, "/Game/Player/BP_Player");
	// AC_Player* player = Cast<AC_Player>(playerClass);
	// player->GetMesh()->SetSkeletalMesh(skeletalMesh);


}


