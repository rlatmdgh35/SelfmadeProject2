#include "C_StartCollision.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/C_Player.h"
#include "Global.h"


AC_StartCollision::AC_StartCollision()
{
	C_Helpers::CreateSceneComponent(this, &Box, "Box");
	// Box->SetRelativeScale3D(FVector(15, 3, 5));
}

void AC_StartCollision::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AC_StartCollision::BeginOverlap);
}

void AC_StartCollision::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AC_StartCollision::TravelPast, 3);
}

void AC_StartCollision::TravelPast()
{
	UWorld* world = GetWorld();
	CheckNull(world);
	world->ServerTravel("/Game/Maps/PastMap");
}


