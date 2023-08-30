#include "C_LockActor.h"
#include "Components/StaticMeshComponent.h"
#include "Player/C_Player.h"
#include "DataAsset/C_DataAsset.h"
#include "Global.h"


AC_LockActor::AC_LockActor()
{

}

void AC_LockActor::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> playerActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Player::StaticClass(), playerActor);
	Player = Cast<AC_Player>(playerActor[0]);

	OnActorBeginOverlap.AddDynamic(this, &AC_LockActor::BeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AC_LockActor::EndOverlap);
}

void AC_LockActor::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	bOverlapping = true;
}

void AC_LockActor::EndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	bOverlapping = false;
}

void AC_LockActor::Interaction() // If Player Has OfficeKey -> Open Door, Another Functions
{
	Player->InteractionType = EInteractionType::Lock;


}

