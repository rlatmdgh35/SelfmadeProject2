#include "C_LockActor.h"
#include "Components/StaticMeshComponent.h"
#include "Player/C_Player.h"
#include "Widgets/C_Lock.h"
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
}

void AC_LockActor::Interaction() // If Player Has OfficeKey -> Open Door, Another Functions
{
	Player->InteractionType = EInteractionType::Lock;

	APlayerController* controller = Cast<APlayerController>(Player->GetController());
	controller->bShowMouseCursor = true;

	Player->bStopLocation = true;
	Player->bStopRotation = true;
	Player->LockWidget->SetVisibility(ESlateVisibility::Visible);
}


