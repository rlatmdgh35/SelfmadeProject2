#include "C_Office.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Player/C_Player.h"
#include "Components/C_PlayerComponent.h"
#include "Global.h"




AC_Office::AC_Office()
{
	C_Helpers::CreateSceneComponent(this, &DefaultSceneComponent, "DefaultSceneComponent");
	C_Helpers::CreateSceneComponent(this, &Box, "Box", DefaultSceneComponent);
	C_Helpers::CreateSceneComponent(this, &Door, "Door", DefaultSceneComponent);


	Box->bHiddenInGame = false; // For Test
}

void AC_Office::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> playerActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Player::StaticClass(), playerActor);
	Player = Cast<AC_Player>(playerActor[0]);

	OnActorBeginOverlap.AddDynamic(this, &AC_Office::BeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AC_Office::EndOverlap);
}

void AC_Office::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	bOverlapping = true;
}

void AC_Office::EndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	bOverlapping = false;
}

void AC_Office::Interaction() // If Player Has OfficeKey -> Open Door, Another Functions
{
	CheckFalse(Player->bHaveOfficeKey);
	C_Log::Print("OfficeOpen");

	Player->PlayerComponent->IsOpenOffice = true;
	Player->bHaveOfficeKey = false;
}


