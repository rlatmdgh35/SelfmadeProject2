#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_Player.generated.h"


UENUM(BlueprintType)
enum class ECurrentMap : uint8
{
	Start, Past, Hotel, End
};

UENUM(BlueprintType)
enum class ECharacterLineType : uint8
{
	StartMap_Start, StartMap_Light, StartMap_JumpScare, StartMap_End, StartMap_Loop, PastMap_Start, HotelMap_Start, OpenEighthGuide, OpenNinthGuide, OpenTenthGuide
};

UENUM(BlueprintType)
enum class EInteractionType : uint8
{
	None, CloseEyes, LightSwitch, Officer, CheckGuide, Door, Lock, Elevator, Max
};

UENUM(BlueprintType)
enum class EEndingType : uint8
{
	Sad, Normal, Happy, Hidden
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterLineTypeSignature, ECharacterLineType, InType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractionTextSignature, EInteractionType, InType);


UCLASS()
class SELFMADEPROJECT2_API AC_Player : public ACharacter
{
	GENERATED_BODY()

public:
	AC_Player();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// This Function Can Read In Blueprint
public:
	UFUNCTION(BlueprintCallable)
		void LineTraceInteraction(AActor* InActor);

// Call Broadcast Function
public:
	UFUNCTION(BlueprintCallable)
		void CallLineOfCharacter(ECharacterLineType InType);

	UFUNCTION(BlueprintImplementableEvent)
		void PlaySoundLine(ECharacterLineType InType);

// Ending Function
public:
	void EndingFunction(EEndingType InType);


// Action Event
private:
	void OnRun();
	void OffRun();
	void CloseEyes();
	void OpenEyes();
	void Interaction();
	void CheckGuide();

	void OnZero();
	void OnOne();
	void OnTwo();
	void OnThree();
	void OnFour();
	void OnFive();
	void OnSix();
	void OnSeven();
	void OnEight();
	void OnNine();
	void OnBackSpace();


// Axis Event
private:
	void OnMoveForward(float InAxis);
	void OnMoveRight(float InAxis);
	void OnHorizontalLook(float InAxis);
	void OnVerticalLook(float InAxis);

// Delegate
public:
	FCharacterLineTypeSignature CharacterLineType;

	UPROPERTY(BlueprintReadOnly)
		FInteractionTextSignature InteractionText;

// SceneComponent
public:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Plane;

	UPROPERTY(VisibleDefaultsOnly)
		class USpotLightComponent* Light;

// ActorComponent
public:
	UPROPERTY(VisibleDefaultsOnly)
		class UC_PlayerComponent* PlayerComponent;

private:
	class UMaterialInstanceConstant* BlackMaterial;
	class UMaterialInstanceDynamic* PlaneMaterial;

public:
	UPROPERTY(BlueprintReadOnly)
		TArray<class AC_Door*> Doors;

	UPROPERTY(BlueprintReadWrite)
		class AC_Security_Officer* Officer;

private:
	class AC_Office* Office;
	class AC_LockActor* LockActor;
	TArray<class AC_LightSwitch*> LightSwitch;
	TArray<class AC_Elevator_Button*> Elevator_Button;

public:
	TSubclassOf<class UC_Interaction> InteractionClass;
	class UC_Interaction* InteractionWidget;

	TSubclassOf<class UC_Guide> Guide;
	class UC_Guide* GuideWidget;

	TSubclassOf<class UC_Lock> Lock;
	class UC_Lock* LockWidget;

	TSubclassOf<class UC_Ending> Ending;
	class UC_Ending* EndingWidget;

	TSubclassOf<class UC_LineOfCharacter> LineOfCharacter;
	UPROPERTY(BlueprintReadOnly)
		class UC_LineOfCharacter* LineOfCharacterWidget;

public:
	UPROPERTY(BlueprintReadWrite)
		ECurrentMap CurrentMap;

	UPROPERTY(BlueprintReadWrite)
		EInteractionType InteractionType = EInteractionType::None;

	UPROPERTY(BlueprintReadOnly)
		bool IsRun;

	UPROPERTY(BlueprintReadOnly)
		bool CanChargeEnergy = false;

	UPROPERTY(BlueprintReadOnly)
		float CurrentEnergy;

	UPROPERTY(BlueprintReadWrite)
		bool bHaveOfficeKey = true;

	UPROPERTY(BlueprintReadWrite)
		bool bTurn = true;

	UPROPERTY(BlueprintReadWrite)
		bool bStopLocation;

	UPROPERTY(BlueprintReadWrite)
		bool bStopRotation;


private:
	FVector MyLocation;
	bool bStartLight = true;

	float Speed;
	float MaxEnergy = 350.f;
	float ChargeWaitTime;
	float SaveDeltaTime;
	float SaveEnergyValue;


};

