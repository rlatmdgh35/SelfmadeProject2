#include "C_Loop.h"
#include "Components/SceneComponent.h"
#include "Player/C_Player.h"
#include "Widgets/C_LineOfCharacter.h"
#include "Global.h"



AC_Loop::AC_Loop()
{
	PrimaryActorTick.bCanEverTick = true;

	C_Helpers::CreateSceneComponent(this, &Root, "Root");
	C_Helpers::GetClass(&LineOfCharacterClass, "/Game/Blueprints/WBP_LineOfCharacter");
}

void AC_Loop::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> playerActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Player::StaticClass(), playerActor);
	Player = Cast<AC_Player>(playerActor[0]);
}

void AC_Loop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bLoop == true)
	{

		if (Player->GetActorLocation().Y <= -10880.f)
		{
			FVector location;
			location.X = Player->GetActorLocation().X;
			location.Y = 1630.f;
			location.Z = Player->GetActorLocation().Z;

			Player->SetActorLocation(location);
		}

		if ((bStart) && (Player->GetActorLocation().Y <= -5000.f))
		{
			Player->CallLineOfCharacter(ECharacterLineType::PastMap_Start);
			bStart = false;
		}
	}
	else
		Destroy();
}
