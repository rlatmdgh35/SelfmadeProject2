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
	StartMap_Start, PastMap_Start, HotelMap_Start, OpenEighthGuide, OpenNinthGuide, OpenTenthGuide
};

UENUM(BlueprintType)
enum class EInteractionType : uint8
{
	None, CheckGuide, Door, Lock, Elevator, Max
};

UENUM(BlueprintType)
enum class EEndingType : uint8
{
	Happy, Sad, Normal, Hidden
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterLineTypeSignature, ECharacterLineType, InType);


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

// Call Broadcast Function
public:
	void CallLineOfCharacter(ECharacterLineType InType);

// This Function Can Read In Blueprint
public:
	UFUNCTION(BlueprintCallable)
		void LineTraceInteraction(AActor* InActor);

// Delegate -> LineOfCharacter
public:
	FCharacterLineTypeSignature CharacterLineType;

// SceneComponent
public:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UCameraComponent* Camera;

// ActorComponent
public:
	UPROPERTY(VisibleDefaultsOnly)
		class UC_PlayerComponent* PlayerComponent;

public:
	UPROPERTY(BlueprintReadOnly)
		TArray<class AC_Door*> Doors;

	UPROPERTY(BlueprintReadOnly)
		class UC_DataAsset* DataAsset;

private:
	class AC_Office* Office;
	class AC_LockActor* LockActor;
	class AC_Elevator_Button* Elevator_Button;

public:
	TSubclassOf<class UC_Guide> Guide;
	class UC_Guide* GuideWidget;

	TSubclassOf<class UC_Lock> Lock;
	class UC_Lock* LockWidget;

	TSubclassOf<class UC_LineOfCharacter> LineOfCharacter;
	class UC_LineOfCharacter* LineOfCharacterWidget;




public:
	UPROPERTY(BlueprintReadWrite)
		ECurrentMap CurrentMap = ECurrentMap::Start;

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


protected:
	float Speed;
	float MaxEnergy = 350.f;
	float ChargeWaitTime;
	float SaveDeltaTime;
	float SaveEnergyValue;


};

