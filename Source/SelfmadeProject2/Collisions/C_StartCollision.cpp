#include "C_StartCollision.h"
#include "Components/BoxComponent.h"
#include "Player/C_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Global.h"


AC_StartCollision::AC_StartCollision()
{
	C_Helpers::CreateSceneComponent(this, &Box, "Box");
	// Box->SetRelativeScale3D(FVector(15, 3, 5));
}

void AC_StartCollision::BeginPlay()
{
	Super::BeginPlay();

	// PastMap Start Location (X=4775.000000,Y=3150.000000,Z=120.000000)

	TArray<AActor*> playerActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Player::StaticClass(), playerActor);
	Player = Cast<AC_Player>(playerActor[0]);

	OnActorBeginOverlap.AddDynamic(this, &AC_StartCollision::BeginOverlap);
}

void AC_StartCollision::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Player->bStopLocation = true;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AC_StartCollision::TravelPast, 3);
}

void AC_StartCollision::TravelPast()
{
	UWorld* world = GetWorld();
	CheckNull(world);
	world->ServerTravel("/Game/Maps/PastMap");

	Player->CurrentMap = ECurrentMap::Past;
	Player->bStopLocation = false;



}


