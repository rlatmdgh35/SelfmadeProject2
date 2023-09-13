#include "C_Player.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/C_PlayerComponent.h"
#include "Widgets/C_Interaction.h"
#include "Widgets/C_LineOfCharacter.h"
#include "Widgets/C_Guide.h"
#include "Widgets/C_Lock.h"
#include "Objects/C_Door.h"
#include "Objects/C_LightSwitch.h"
#include "Objects/C_Office.h"
#include "Objects/C_LockActor.h"
#include "Objects/C_Elevator_Button.h"
#include "Officer/C_Security_Officer.h"
#include "Global.h"


AC_Player::AC_Player()
{
	// || Create SceneComponent ||
	C_Helpers::CreateSceneComponent(this, &Camera, "Camera", GetMesh());
	C_Helpers::CreateSceneComponent(this, &Plane, "Plane", Camera);

	// || Get Asset_DataAsset ||
	C_Helpers::CreateActorComponent(this, &PlayerComponent, "PlayerComponent");

	USkeletalMesh* meshAsset;
	C_Helpers::GetAsset(&meshAsset, "/Game/Character/Start/Mesh/Ch28_nonPBR");

	TSubclassOf<UAnimInstance> animInstanceClass;
	C_Helpers::GetClass(&animInstanceClass, "/Game/Player/Blueprint/ABP_Player_Start");

	UStaticMesh* planeAsset;
	C_Helpers::GetAsset(&planeAsset, "/Game/StaticMeshes/SM_Plane");
	
	UMaterial* blackMaterial;
	C_Helpers::GetAsset(&blackMaterial, "/Game/Materials/MAT_Black");

	// Mesh Setting
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, 270, 0));
	GetMesh()->SetSkeletalMesh(meshAsset);
	GetMesh()->SetAnimInstanceClass(animInstanceClass);

	// Camera Setting
	Camera->SetRelativeLocation(FVector(0, 44.5, 157.5));
	Camera->SetRelativeRotation(FRotator(0, 90, 0));
	Camera->bUsePawnControlRotation = true;

	// Planes To Act As Blindfolds Setting
	Plane->SetStaticMesh(planeAsset);
	Plane->SetRelativeLocationAndRotation(FVector(25, 0, 0), FRotator(90, 0, 0));
	Plane->SetMaterial(0, blackMaterial);
	Plane->SetVisibility(false);

	// Movement
	GetCharacterMovement()->MaxWalkSpeed = 400.f;

	C_Helpers::GetClass(&InteractionClass, "/Game/Blueprints/Widgets/WBP_Interaction");
	C_Helpers::GetClass(&LineOfCharacter, "/Game/Blueprints/Widgets/WBP_LineOfCharacter");
	C_Helpers::GetClass(&Guide, "/Game/Blueprints/Widgets/WBP_Guide");
	C_Helpers::GetClass(&Lock, "/Game/Blueprints/Widgets/WBP_Lock");
}

void AC_Player::BeginPlay()
{
	CurrentEnergy = MaxEnergy;

	TArray<AActor*> doorActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Door::StaticClass(), doorActors);
	for (int32 i = 0; i < doorActors.Num(); i++)
		Doors.Add(Cast<AC_Door>(doorActors[i]));

	TArray<AActor*> lightSwitchActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_LightSwitch::StaticClass(), lightSwitchActors);
	for (int32 i = 0; i < lightSwitchActors.Num(); i++)
		LightSwitch.Add(Cast<AC_LightSwitch>(lightSwitchActors[i]));

	TArray<AActor*> buttonActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Elevator_Button::StaticClass(), buttonActors);
	for (int32 i = 0; i < buttonActors.Num(); i++)
		Elevator_Button.Add(Cast<AC_Elevator_Button>(buttonActors[i]));

	TArray<AActor*> officeActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Office::StaticClass(), officeActor);
	if (officeActor.Num() > 0)
		Office = Cast<AC_Office>(officeActor[0]);

	TArray<AActor*> lockActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_LockActor::StaticClass(), lockActor);
	if(lockActor.Num() > 0)
		LockActor = Cast<AC_LockActor>(lockActor[0]);
	
	APlayerController* controller = Cast<APlayerController>(GetController());

	InteractionWidget = CreateWidget<UC_Interaction>(controller, InteractionClass);
	InteractionWidget->AddToViewport();
	InteractionWidget->BeginPlay(this);

	LockWidget = CreateWidget<UC_Lock>(controller, Lock);
	LockWidget->AddToViewport();
	LockWidget->BeginPlay(this);
	LockWidget->SetVisibility(ESlateVisibility::Hidden);

	GuideWidget = CreateWidget<UC_Guide>(controller, Guide);
	GuideWidget->BeginPlay(this);
	GuideWidget->AddToViewport();
	GuideWidget->SetVisibility(ESlateVisibility::Hidden);

	LineOfCharacterWidget = CreateWidget<UC_LineOfCharacter>(controller, LineOfCharacter);
	LineOfCharacterWidget->BeginPlay(this);
	LineOfCharacterWidget->AddToViewport();

	Super::BeginPlay();
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
		PlayerComponent->IsCanRun = false;
	else
		PlayerComponent->IsCanRun = true;
}

void AC_Player::LineTraceInteraction(AActor* Actor)
{
	for (int32 i = 0; i < LightSwitch.Num(); i++)
	{
		if (LightSwitch[i] == Cast<AC_LightSwitch>(Actor))
		{
			CheckTrue(InteractionType == EInteractionType::CheckGuide);

			LightSwitch[i]->bCanCall = true;
			InteractionText.Broadcast(EInteractionType::LightSwitch);
		}
		else
		{
			LightSwitch[i]->bCanCall = false;
			InteractionText.Broadcast(EInteractionType::None);
		}
	}

	for (int32 i = 0; i < Doors.Num(); i++)
	{
		if (Doors[i] == Cast<AC_Door>(Actor))
		{
			CheckTrue(InteractionType == EInteractionType::CheckGuide);
			CheckTrue(InteractionType == EInteractionType::Lock);

			Doors[i]->bCanCall = true;
			InteractionText.Broadcast(EInteractionType::Door);

			break;
		}
		else
		{
			Doors[i]->bCanCall = false;
			InteractionText.Broadcast(EInteractionType::None);
		}
	}

	for (int32 i = 0; i < Elevator_Button.Num(); i++)
	{
		if (Elevator_Button[i] == Cast<AC_Elevator_Button>(Actor))
		{
			Elevator_Button[i]->bCanCall = true;
			InteractionText.Broadcast(EInteractionType::Elevator);
			
			break;
		}
		else
		{
			Elevator_Button[i]->bCanCall = false;
			InteractionText.Broadcast(EInteractionType::None);
		}
	}

	if (Officer != nullptr)
	{
		CheckFalse(CurrentMap == ECurrentMap::Start);

		if (Cast<AC_Security_Officer>(Actor) != nullptr)
		{
			Officer->bCanCall = true;
			InteractionText.Broadcast(EInteractionType::Officer);
		}
		else
		{
			Officer->bCanCall = false;
			InteractionText.Broadcast(EInteractionType::None);
		}
	}

	if (LockActor != nullptr)
	{
		CheckTrue(PlayerComponent->OpenGuide.IsOpenTenth == true);

		if (Cast<AC_LockActor>(Actor) != nullptr)
		{
			LockActor->bCanCall = true;
			InteractionText.Broadcast(EInteractionType::Lock);
		}
		else
		{
			LockActor->bCanCall = false;
			InteractionText.Broadcast(EInteractionType::None);
		}
	}
}

void AC_Player::CallLineOfCharacter(ECharacterLineType InType)
{
	if (CharacterLineType.IsBound())
		CharacterLineType.Broadcast(InType);

	PlaySoundLine(InType);
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
	PlayerInputComponent->BindAction("Zero", EInputEvent::IE_Pressed, this, &AC_Player::OnZero);
	PlayerInputComponent->BindAction("One", EInputEvent::IE_Pressed, this, &AC_Player::OnOne);
	PlayerInputComponent->BindAction("Two", EInputEvent::IE_Pressed, this, &AC_Player::OnTwo);
	PlayerInputComponent->BindAction("Three", EInputEvent::IE_Pressed, this, &AC_Player::OnThree);
	PlayerInputComponent->BindAction("Four", EInputEvent::IE_Pressed, this, &AC_Player::OnFour);
	PlayerInputComponent->BindAction("Five", EInputEvent::IE_Pressed, this, &AC_Player::OnFive);
	PlayerInputComponent->BindAction("Six", EInputEvent::IE_Pressed, this, &AC_Player::OnSix);
	PlayerInputComponent->BindAction("Seven", EInputEvent::IE_Pressed, this, &AC_Player::OnSeven);
	PlayerInputComponent->BindAction("Eight", EInputEvent::IE_Pressed, this, &AC_Player::OnEight);
	PlayerInputComponent->BindAction("Nine", EInputEvent::IE_Pressed, this, &AC_Player::OnNine);
	PlayerInputComponent->BindAction("BackSpace", EInputEvent::IE_Pressed, this, &AC_Player::OnBackSpace);


	// Axis Event
	PlayerInputComponent->BindAxis("MoveForward", this, &AC_Player::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AC_Player::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &AC_Player::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &AC_Player::OnVerticalLook);
}

void AC_Player::OnRun()
{
	CheckFalse(CurrentMap == ECurrentMap::Hotel);
	CheckTrue(CurrentEnergy <= 50);

	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	IsRun = true;
}

void AC_Player::OffRun()
{
	CheckFalse(CurrentMap == ECurrentMap::Hotel);

	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	IsRun = false;
}

void AC_Player::CloseEyes()
{
	PlayerComponent->IsOpenEyes = false;
	if (InteractionType == EInteractionType::CheckGuide)
	{
		bTurn = false;
		CheckGuide();
	}
	InteractionType = EInteractionType::CloseEyes;

	Plane->SetVisibility(true);
}

void AC_Player::OpenEyes()
{
	PlayerComponent->IsOpenEyes = true;
	InteractionType = EInteractionType::None;

	Plane->SetVisibility(false);
}

void AC_Player::Interaction()
{
	if ((Officer != nullptr) && (Officer->bCanCall == true))
		CallLineOfCharacter(ECharacterLineType::StartMap_End);


	if ((Office != nullptr) && (Office->IsOverlapped()))
		Office->Interaction();

	if ((LockActor != nullptr) && (LockActor->bCanCall == true) && (PlayerComponent->OpenGuide.IsOpenTenth == false))
	{
		CheckTrue(InteractionType == EInteractionType::CheckGuide);
		InteractionType = EInteractionType::Lock;
		LockActor->Interaction();
	}

	for (int32 i = 0; i < LightSwitch.Num(); i++)
	{
		if (LightSwitch[i]->bCanCall == true)
		{
			LightSwitch[i]->Interaction();
			break;
		}
	}
	
	for (int32 i = 0; i < Elevator_Button.Num(); i++)
	{
		if (Elevator_Button[i]->bCanCall == true)
		{
			InteractionType = EInteractionType::Elevator;
			Elevator_Button[i]->Interaction();
			break;
		}
	}

	for (int32 i = 0; i < Doors.Num(); i++)
	{
		if (Doors[i]->bCanCall == true)
		{
			InteractionType = EInteractionType::Door;
			Doors[i]->Interaction();
			break;
		}
	}

}

void AC_Player::CheckGuide()
{
	CheckFalse(CurrentMap == ECurrentMap::Hotel);

	APlayerController* controller = Cast<APlayerController>(GetController());
	if (bTurn)
	{
		CheckTrue(InteractionType == EInteractionType::Lock);

		GuideWidget->ShowFirstPage();
		controller->bShowMouseCursor = true;
		GuideWidget->SetVisibility(ESlateVisibility::Visible);
		InteractionType = EInteractionType::CheckGuide;

		bTurn = false;
	}
	else
	{
		controller->bShowMouseCursor = false;
		GuideWidget->SetVisibility(ESlateVisibility::Hidden);
		InteractionType = EInteractionType::None;

		bTurn = true;
	}
}

void AC_Player::OnZero()
{
	CheckFalse(InteractionType == EInteractionType::Lock);

	LockWidget->SetTextNum(FText::FromString("0"));
}

void AC_Player::OnOne()
{
	CheckFalse(InteractionType == EInteractionType::Lock);

	LockWidget->SetTextNum(FText::FromString("1"));
}

void AC_Player::OnTwo()
{
	CheckFalse(InteractionType == EInteractionType::Lock);

	LockWidget->SetTextNum(FText::FromString("2"));
}

void AC_Player::OnThree()
{
	CheckFalse(InteractionType == EInteractionType::Lock);

	LockWidget->SetTextNum(FText::FromString("3"));
}

void AC_Player::OnFour()
{
	CheckFalse(InteractionType == EInteractionType::Lock);

	LockWidget->SetTextNum(FText::FromString("4"));
}

void AC_Player::OnFive()
{
	CheckFalse(InteractionType == EInteractionType::Lock);

	LockWidget->SetTextNum(FText::FromString("5"));
}

void AC_Player::OnSix()
{
	CheckFalse(InteractionType == EInteractionType::Lock);

	LockWidget->SetTextNum(FText::FromString("6"));
}

void AC_Player::OnSeven()
{
	CheckFalse(InteractionType == EInteractionType::Lock);

	LockWidget->SetTextNum(FText::FromString("7"));
}

void AC_Player::OnEight()
{
	CheckFalse(InteractionType == EInteractionType::Lock);

	LockWidget->SetTextNum(FText::FromString("8"));
}

void AC_Player::OnNine()
{
	CheckFalse(InteractionType == EInteractionType::Lock);

	LockWidget->SetTextNum(FText::FromString("9"));
}

void AC_Player::OnBackSpace()
{
	CheckFalse(InteractionType == EInteractionType::Lock);

	LockWidget->PressBackSpace();
}

void AC_Player::OnMoveForward(float InAxis)
{
	CheckTrue(FMath::IsNearlyZero(InAxis));
	CheckTrue(bStopLocation);

	FRotator rotator = FRotator(0.f, GetControlRotation().Yaw, 0.f);
	FVector direction = FQuat(rotator).GetForwardVector();

	AddMovementInput(direction, InAxis);
}

void AC_Player::OnMoveRight(float InAxis)
{
	CheckTrue(FMath::IsNearlyZero(InAxis));
	CheckTrue(bStopLocation);

	FRotator rotator = FRotator(0.f, GetControlRotation().Yaw, 0.f);
	FVector direction = FQuat(rotator).GetRightVector();

	AddMovementInput(direction, InAxis);
}

void AC_Player::OnHorizontalLook(float InAxis)
{
	CheckTrue(bStopRotation);

	float speed = 45.f;
	AddControllerYawInput(InAxis * speed * GetWorld()->GetDeltaSeconds());
}

void AC_Player::OnVerticalLook(float InAxis)
{
	CheckTrue(bStopRotation);

	float speed = 45.f;
	AddControllerPitchInput(InAxis * speed * GetWorld()->GetDeltaSeconds());
}