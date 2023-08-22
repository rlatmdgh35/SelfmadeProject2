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


}

void AC_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Action Event
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &AC_Player::OnRun);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &AC_Player::OffRun);

	// Axis Event
	PlayerInputComponent->BindAxis("MoveForward", this, &AC_Player::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AC_Player::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &AC_Player::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &AC_Player::OnVerticalLook);

}

void AC_Player::OnRun()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void AC_Player::OffRun()
{
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
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