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

	APlayerController* controller = Cast<APlayerController>(Player->GetController());
	LineOfCharacter = CreateWidget<UC_LineOfCharacter>(controller, LineOfCharacterClass);

	LineOfCharacter->PastMapSetOffLoop.AddDynamic(this, &AC_Loop::SetOffLoop);
}

void AC_Loop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckFalse(bLoop);
	CheckFalse(Player->GetActorLocation().X <= 2500.f);
	CheckFalse(Player->GetActorLocation().Y <= -11420.f);

	FVector location;
	location.X = Player->GetActorLocation().X;
	location.Y = 1100.f;
	location.Z = Player->GetActorLocation().Z;

	Player->SetActorLocation(location);
}

void AC_Loop::SetOffLoop()
{
	bLoop = false;
}