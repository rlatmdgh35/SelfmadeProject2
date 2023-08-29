#include "C_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Widgets/C_Guide.h"
#include "Component/C_PlayerComponent.h"
#include "DataAsset/C_DataAsset.h"
#include "Meshes/C_Door.h"
#include "Objects/C_Office.h"
#include "Blueprint/UserWidget.h"
#include "Global.h"


AC_Player::AC_Player()
{
	// || Create SceneComponent ||
	C_Helpers::CreateSceneComponent(this, &Camera, "Camera", GetMesh());

	// || Create ActorComponent ||
	C_Helpers::CreateActorComponent(this, &PlayerComponent, "Component");

	// || Get Asset_DataAsset ||
	C_Helpers::GetAsset(&DataAsset, "/Game/Player/DA_Player");
	PlayerComponent->DataAsset = DataAsset;

	USkeletalMesh* meshAsset;
	C_Helpers::GetAsset(&meshAsset, "/Game/Character/Start/Mesh/Ch28_nonPBR");

	TSubclassOf<UAnimInstance> animInstanceClass;
	C_Helpers::GetClass(&animInstanceClass, "/Game/Player/BluePrint/ABP_Player_Start");
	GetMesh()->SetAnimInstanceClass(animInstanceClass);


	// Mesh Setting
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, 270, 0));
	GetMesh()->SetSkeletalMesh(meshAsset);

	// Camera Setting
	Camera->SetRelativeLocation(FVector(0, 44.5, 157.5));
	Camera->SetRelativeRotation(FRotator(0, 90, 0));
	Camera->bUsePawnControlRotation = true;


	// Movement
	GetCharacterMovement()->MaxWalkSpeed = 400.f;

	C_Helpers::GetClass(&Guide, "/Game/Blueprints/WBP_Guide");

}

void AC_Player::BeginPlay()
{
	Super::BeginPlay();

	CurrentEnergy = MaxEnergy;

	TArray<AActor*> doorActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Door::StaticClass(), doorActors);
	if (doorActors.Num() > 0)
	{
		for (int32 i = 0; i < doorActors.Num(); i++)
		{
			Doors.Add(Cast<AC_Door>(doorActors[i]));
		}
	}

	TArray<AActor*> officeActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Office::StaticClass(), officeActor);
	if (officeActor.Num() > 0)
		Office = Cast<AC_Office>(officeActor[0]);


	APlayerController* controller = Cast<APlayerController>(GetController());
	GuideWidget = CreateWidget<UC_Guide>(controller, Guide);
	GuideWidget->AddToViewport();


}

void AC_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Speed = GetVelocity().Size2D();

	if (IsRun)
	{
		if (CurrentEnergy != 0)
		{
			SaveDeltaTime = 0.f;
			CanChargeEnergy = false;
			CurrentEnergy -= Speed / 10.f * DeltaTime;
			CurrentEnergy = FMath::Clamp(CurrentEnergy, 0.f, 1000.f);
		}
		else
			OffRun();
	}
	else if (CanChargeEnergy == true)
	{
		SaveDeltaTime += DeltaTime;
		if (ChargeWaitTime != 0)
		{
			SaveDeltaTime = FMath::Clamp(SaveDeltaTime, 0.f, ChargeWaitTime);
			C_Log::Print("FlowTime Value : " + FString::SanitizeFloat(SaveDeltaTime), 1);
			C_Log::Print("WaitTime Value : " + FString::SanitizeFloat(ChargeWaitTime), 2);
			CurrentEnergy = SaveEnergyValue + ((MaxEnergy - SaveEnergyValue) / ChargeWaitTime * SaveDeltaTime);
			CurrentEnergy = FMath::Clamp(CurrentEnergy, 0.f, 1000.f);
		}
	}
	else
	{
		SaveDeltaTime += DeltaTime;
		ChargeWaitTime = 3.5f * (1.f - CurrentEnergy / MaxEnergy);
		if (SaveDeltaTime >= ChargeWaitTime && ChargeWaitTime != 0)
		{
			SaveEnergyValue = CurrentEnergy;
			SaveDeltaTime = 0.f;
			CanChargeEnergy = true;
		}
	}

	if (CurrentEnergy <= 50)
		DataAsset->IsCanRun = false;
	else
		DataAsset->IsCanRun = true;

	// On/Off Widget
	// --------------------------------------------------------
	if (bTurn)
		GuideWidget->SetVisibility(ESlateVisibility::Hidden);
	else
		GuideWidget->SetVisibility(ESlateVisibility::Visible);
	// --------------------------------------------------------

}

void AC_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Action Event
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &AC_Player::OnRun);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &AC_Player::OffRun);
	PlayerInputComponent->BindAction("CloseEyes", EInputEvent::IE_Pressed, this, &AC_Player::CloseEyes);
	PlayerInputComponent->BindAction("CloseEyes", EInputEvent::IE_Released, this, &AC_Player::OpenEyes);
	PlayerInputComponent->BindAction("Interaction", EInputEvent::IE_Pressed, this, &AC_Player::Interaction);
	PlayerInputComponent->BindAction("CheckGuide", EInputEvent::IE_Pressed, this, &AC_Player::CheckGuide);


	// Axis Event
	PlayerInputComponent->BindAxis("MoveForward", this, &AC_Player::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AC_Player::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &AC_Player::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &AC_Player::OnVerticalLook);
}

void AC_Player::OnRun()
{
	CheckTrue(CurrentMap == ECurrentMap::Past);
	CheckTrue(CurrentEnergy <= 50);

	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	IsRun = true;
}

void AC_Player::OffRun()
{
	CheckTrue(CurrentMap == ECurrentMap::Past);

	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	IsRun = false;
}

void AC_Player::CloseEyes()
{
	DataAsset->IsOpenEyes = false;
}

void AC_Player::OpenEyes()
{
	DataAsset->IsOpenEyes = true;
}

void AC_Player::CheckGuide()
{
	if (bTurn)
	{
		GuideWidget->ShowFirstPage();
		APlayerController* controller = Cast<APlayerController>(GetController());
		controller->bShowMouseCursor = true;

		bTurn = false;
	}
	else
	{
		APlayerController* controller = Cast<APlayerController>(GetController());
		controller->bShowMouseCursor = false;

		bTurn = true;
	}
}

void AC_Player::Interaction()
{
	if (Doors.Num() > 0)
	{
		for (int32 i = 0; i < Doors.Num(); i++)
		{
			if (Doors[i]->IsOverrlaped())
			{
				Doors[i]->Interaction();
				break;
			}
		}
	}

	if ((Office != nullptr) && (Office->IsOverlapped()))
		Office->Interaction();
}

void AC_Player::OnMoveForward(float InAxis)
{
	CheckTrue(FMath::IsNearlyZero(InAxis));


	FRotator rotator = FRotator(0.f, GetControlRotation().Yaw, 0.f);
	FVector direction = FQuat(rotator).GetForwardVector();

	AddMovementInput(direction, InAxis);
}

void AC_Player::OnMoveRight(float InAxis)
{
	CheckTrue(FMath::IsNearlyZero(InAxis));

	FRotator rotator = FRotator(0.f, GetControlRotation().Yaw, 0.f);
	FVector direction = FQuat(rotator).GetRightVector();

	AddMovementInput(direction, InAxis);
}

void AC_Player::OnHorizontalLook(float InAxis)
{
	CheckTrue(bTravelMap);

	float speed = 45.f;
	AddControllerYawInput(InAxis * speed * GetWorld()->GetDeltaSeconds());
}

void AC_Player::OnVerticalLook(float InAxis)
{
	CheckTrue(bTravelMap);

	float speed = 45.f;
	AddControllerPitchInput(InAxis * speed * GetWorld()->GetDeltaSeconds());
}