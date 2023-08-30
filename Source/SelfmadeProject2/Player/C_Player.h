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
enum class EInteractionType : uint8
{
	Door, Lock, Max
};

UENUM(BlueprintType)
enum class EEndingType : uint8
{
	Happy, Sad, Normal, Hidden
};

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



// Axis Event
private:
	void OnMoveForward(float InAxis);
	void OnMoveRight(float InAxis);
	void OnHorizontalLook(float InAxis);
	void OnVerticalLook(float InAxis);



// SceneComponent
private:
	UPROPERTY(VisibleDefaultsOnly)
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
	
	class AC_Office* Office;
	class AC_LockActor* LockActor;

private:
	TSubclassOf<class UC_Guide> Guide;
	class UC_Guide* GuideWidget;

	TSubclassOf<class UC_Lock> Lock;
	class UC_Lock* LockWidget;


protected:
	UPROPERTY(BlueprintReadOnly)
		bool IsRun;
	
	UPROPERTY(BlueprintReadOnly)	
		bool CanChargeEnergy = false;

	UPROPERTY(BlueprintReadOnly)
		float CurrentEnergy;

public:
	UPROPERTY(BlueprintReadWrite)
		ECurrentMap CurrentMap;

	UPROPERTY(BlueprintReadWrite)
		EInteractionType InteractionType;
	
	UPROPERTY(BlueprintReadWrite)
		bool bTurn = true;

protected:
	float Speed;
	float MaxEnergy = 350.f;
	float ChargeWaitTime;
	float SaveDeltaTime;
	float SaveEnergyValue;

public:
	bool bTravelMap;

	UPROPERTY(BlueprintReadWrite)
		bool bHaveOfficeKey = true;


};

