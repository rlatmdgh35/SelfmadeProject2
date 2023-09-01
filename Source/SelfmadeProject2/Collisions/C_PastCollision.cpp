#include "C_PastCollision.h"
#include "Components/BoxComponent.h"
#include "Player/C_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Global.h"


AC_PastCollision::AC_PastCollision()
{
	C_Helpers::CreateSceneComponent(this, &Box, "Box");
	Box->SetRelativeScale3D(FVector(15, 3, 5));
}

void AC_PastCollision::BeginPlay()
{
	Super::BeginPlay();

	// PastMap Start Location (X=4775.000000,Y=3150.000000,Z=120.000000)

	TArray<AActor*> playerActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Player::StaticClass(), playerActor);
	Player = Cast<AC_Player>(playerActor[0]);

	OnActorBeginOverlap.AddDynamic(this, &AC_PastCollision::BeginOverlap);
}

void AC_PastCollision::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Player->bStopLocation = true;
	Player->bStopRotation = true;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AC_PastCollision::TravelHotel, 3);
}

void AC_PastCollision::TravelHotel()
{
	UWorld* world = GetWorld();
	CheckNull(world);

	world->ServerTravel("/Game/Maps/HotelMap");
	Player->bStopLocation = false;
	Player->bStopRotation = false;
	Player->CallLineOfCharacter(ECharacterLineType::HotelMap_Start);


}


