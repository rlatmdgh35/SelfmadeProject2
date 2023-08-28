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
	Door, Max
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
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UC_PlayerComponent* PlayerComponent;

public:
	UPROPERTY(BlueprintReadOnly)
		TArray<class AC_Door*> Doors;

private:
	class UC_DataAsset* DataAsset;

protected:
	UPROPERTY(BlueprintReadOnly)
		bool IsRun;
	
	UPROPERTY(BlueprintReadOnly)	
		bool CanChargeEnergy = false;

	UPROPERTY(BlueprintReadOnly)
		float CurrentEnergy;

protected:
	UPROPERTY(BlueprintReadWrite)
		ECurrentMap CurrentMap;

	float Speed;
	float MaxEnergy = 350.f;
	float ChargeWaitTime;
	float SaveDeltaTime;
	float SaveEnergyValue;
	bool bTurn = true;

public:
	bool bTravelMap;



};

