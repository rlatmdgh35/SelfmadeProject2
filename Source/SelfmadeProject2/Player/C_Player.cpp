#include "C_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Component/C_PlayerComponent.h"
#include "DataAsset/C_DataAsset.h"
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
	C_Helpers::GetClass(&animInstanceClass, "/Game/Player/BluePrint/ABP_Player");
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



}

void AC_Player::BeginPlay()
{
	Super::BeginPlay();

	CurrentEnergy = MaxEnergy;
	SaveEnergy = CurrentEnergy;
	Ratio = CurrentEnergy / MaxEnergy;
	Pow = FMath::Square(Ratio);
}

void AC_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Speed = GetVelocity().Size2D();
	if (IsRun)
	{
		CanChargeEnergy = false;
		CurrentEnergy -= Speed / 5 * DeltaTime;
		FMath::Clamp(CurrentEnergy, 0.f, 350.f);
	}
	else
	{
		if (CanChargeEnergy == false)
		{
			FTimerHandle timerHandle;
			GetWorldTimerManager().SetTimer(timerHandle, this, &AC_Player::NotBlockCharge, (3.5 * Pow));
		}
		else
		{
			SaveDeltaTime += DeltaTime;
			CurrentEnergy = ((MaxEnergy - CurrentEnergy) / Pow) * SaveDeltaTime;
			FMath::Clamp(CurrentEnergy, 0.f, 350.f);
		}

		
	}
}

void AC_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Action Event
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &AC_Player::OnRun);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &AC_Player::OffRun);
	PlayerInputComponent->BindAction("CloseEyes", EInputEvent::IE_Pressed, this, &AC_Player::CloseEyes);
	PlayerInputComponent->BindAction("CloseEyes", EInputEvent::IE_Released, this, &AC_Player::OpenEyes);

	// Axis Event
	PlayerInputComponent->BindAxis("MoveForward", this, &AC_Player::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AC_Player::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &AC_Player::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &AC_Player::OnVerticalLook);

}

void AC_Player::OnRun()
{
	CheckTrue(CurrentEnergy < 30);

	IsRun = true;
}

void AC_Player::OffRun()
{
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
	float speed = 45.f;
	AddControllerYawInput(InAxis * speed * GetWorld()->GetDeltaSeconds());
}

void AC_Player::OnVerticalLook(float InAxis)
{
	float speed = 45.f;
	AddControllerPitchInput(InAxis * speed * GetWorld()->GetDeltaSeconds());
}

void AC_Player::NotBlockCharge()
{
	SaveEnergy = CurrentEnergy;
	Ratio = CurrentEnergy / MaxEnergy;
	Pow = FMath::Pow(Ratio, 2);


	CanChargeEnergy = true;
}