#include "C_Door.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Player/C_Player.h"
#include "Global.h"



AC_Door::AC_Door()
{
	C_Helpers::CreateSceneComponent<USceneComponent>(this, &DefaultSceneComponent, "DefaultSceneComoponent");

	C_Helpers::CreateSceneComponent<USceneComponent>(this, &DoorRoot, "DoorRoot", DefaultSceneComponent);
	C_Helpers::CreateSceneComponent<UStaticMeshComponent>(this, &Door, "Door", DoorRoot);
	C_Helpers::CreateSceneComponent<UStaticMeshComponent>(this, &DoorHandle_F, "DoorHandle_F", Door);
	C_Helpers::CreateSceneComponent<UStaticMeshComponent>(this, &DoorHandle_B, "DoorHandle_B", Door);
	C_Helpers::CreateSceneComponent<USceneComponent>(this, &Corner_R, "Corner_R", DefaultSceneComponent);
	C_Helpers::CreateSceneComponent<USceneComponent>(this, &Corner_L, "Corner_L", DefaultSceneComponent);
	C_Helpers::CreateSceneComponent<UBoxComponent>(this, &Box, "BoxCollision", DefaultSceneComponent);

	DoorRoot->SetRelativeLocation(FVector(0, 62, 0));
	
	Door->SetRelativeLocationAndRotation(FVector(0, -62, 0), FRotator(0, 90, 0));

	UStaticMesh* doorHandle_F;
	C_Helpers::GetAsset(&doorHandle_F, "/Game/StaticMeshes/SM_DoorHandle");
	DoorHandle_F->SetStaticMesh(doorHandle_F);
	DoorHandle_F->SetRelativeLocation(FVector(-55, 0, 100));
	DoorHandle_F->SetRelativeRotation(FRotator(0, 180, 90));

	UStaticMesh* doorHandle_B;
	C_Helpers::GetAsset(&doorHandle_B, "/Game/StaticMeshes/SM_DoorHandle");
	DoorHandle_B->SetStaticMesh(doorHandle_B);
	DoorHandle_B->SetRelativeLocation(FVector(-55.f, 5.75f, 100.f));
	DoorHandle_B->SetRelativeRotation(FRotator(0, 180, 270));

	float xScale = Door->GetRelativeScale3D().X;
	float yScale = Door->GetRelativeScale3D().Y;
	float zScale = Door->GetRelativeScale3D().Z;

	Corner_R->SetRelativeLocation(FVector(3.5f * xScale, 60.f * yScale, 100.f * zScale));
	Corner_L->SetRelativeLocation(FVector(3.5f * xScale, -60.f * yScale, 100.f * zScale));


	Box->SetRelativeLocationAndRotation(FVector(0, 0, 100), FRotator(0, 90, 0));
	Box->SetRelativeScale3D(FVector(1.75, 3, 3));
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
	FVector rightVector = RootComponent->GetRelativeRotationFromWorld(quat).GetRightVector();
	FVector directionalVector = (Player->GetActorLocation() - GetActorLocation());
	directionalVector.Z = 0;

	// 
	FVector playerLocation = Player->GetActorLocation();
	FVector playerForward = Player->GetActorForwardVector();
	FVector doorForward = -1 * GetActorRightVector();

	//
	FVector corner_R = Corner_R->GetComponentLocation();
	FVector normal_R = (playerLocation - corner_R).GetSafeNormal2D();
	FVector corner_L = Corner_L->GetComponentLocation();
	FVector normal_L = (playerLocation - corner_L).GetSafeNormal2D();

	float crossResult = FVector::CrossProduct(rightVector, directionalVector).Z;
	float cross_R = FVector::CrossProduct(normal_R, playerForward).Z * -1;
	float cross_L = FVector::CrossProduct(normal_L, playerForward).Z;

	C_Log::Print("L : " + FString::SanitizeFloat(cross_L));
	C_Log::Print("R : " + FString::SanitizeFloat(cross_R));

	if (crossResult >= 0)
	{
		CheckFalse(cross_R <= 0 && cross_L <= 0);
		Rotation = 1.f;
	}
	else
	{
		CheckFalse(cross_R >= 0 && cross_L >= 0);
		Rotation = -1.f;
	}

	if (bMoving || bOpen)
		Rotation = SaveRotation;
	
	StartTimeline();
}