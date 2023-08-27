#include "C_Door.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Player/C_Player.h"
#include "Global.h"



AC_Door::AC_Door()
{
	C_Helpers::CreateSceneComponent<USceneComponent>(this, &DefaultSceneComponent, "DafaultSceneComponent");

	C_Helpers::CreateSceneComponent<UStaticMeshComponent>(this, &Door, "Door", DefaultSceneComponent);
	C_Helpers::CreateSceneComponent<UStaticMeshComponent>(this, &DoorHandle_F, "DoorHandle_F", Door);
	C_Helpers::CreateSceneComponent<UStaticMeshComponent>(this, &DoorHandle_B, "DoorHandle_B", Door);
	C_Helpers::CreateSceneComponent<UBoxComponent>(this, &Box, "BoxCollision", DefaultSceneComponent);

	UStaticMesh* doorHandle_F;
	C_Helpers::GetAsset(&doorHandle_F, "/Game/StaticMeshes/SM_DoorHandle");
	DoorHandle_F->SetStaticMesh(doorHandle_F);
	DoorHandle_F->SetRelativeLocation(FVector(-55.f, 0.f, 100.f));
	DoorHandle_F->SetRelativeRotation(FRotator(0.f, 180.f, 90.f));

	UStaticMesh* doorHandle_B;
	C_Helpers::GetAsset(&doorHandle_B, "/Game/StaticMeshes/SM_DoorHandle");
	DoorHandle_B->SetStaticMesh(doorHandle_B);
	DoorHandle_B->SetRelativeLocation(FVector(-55.f, 5.75f, 100.f));
	DoorHandle_B->SetRelativeRotation(FRotator(0.f, 180.f, 270.f));

	Box->SetRelativeLocation(FVector(0, 0, 100));
	Box->SetRelativeScale3D(FVector(1.75f, 3.f, 3.f));


}

void AC_Door::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> playerActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Player::StaticClass(), playerActor);
	Player = Cast<AC_Player>(playerActor[0]);


	OnActorBeginOverlap.AddDynamic(this, &AC_Door::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AC_Door::ActorEndOverlap);

}

void AC_Door::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	bOverlapped = true;
}

void AC_Door::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	bOverlapped = false;
}

void AC_Door::Interaction()
{
	// 
	FQuat quat;
	FVector rightVector = DefaultSceneComponent->GetRelativeRotationFromWorld(quat).GetForwardVector();
	FVector directionalVector = Player->GetActorLocation() - GetActorLocation();
	directionalVector.Z = 0;
	float dotResult = UKismetMathLibrary::Dot_VectorVector(rightVector, directionalVector);

	// 
	FVector doorForward = -1 * GetActorRightVector();
	FVector playerForward = Player->GetActorForwardVector();
	float dotResult2 = UKismetMathLibrary::Dot_VectorVector(doorForward, playerForward);
	float cos45 = FMath::Sqrt(2) / 2;

	

	if (dotResult <= 0)
	{
		Rotation = 1.f;
		CheckFalse(dotResult2 >= cos45);
	}
	else
	{
		Rotation = -1.f;
		CheckFalse(dotResult2 <= -1 * cos45);
	}


	if ((bClosing || bOpen) == true)
		Rotation = SaveRotation;

	StartTimeline();
}