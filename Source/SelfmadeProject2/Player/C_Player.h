#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_Player.generated.h"


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


	// Axis Event
private:
	void OnMoveForward(float InAxis);
	void OnMoveRight(float InAxis);
	void OnHorizontalLook(float InAxis);
	void OnVerticalLook(float InAxis);

private:
	void NotBlockCharge();

	// SceneComponent
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

	// ActorComponent
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UC_PlayerComponent* PlayerComponent;


private:
	class UC_DataAsset* DataAsset;

private:
	float SaveDeltaTime;

protected:
	UPROPERTY(BlueprintReadOnly)
		bool IsRun;
	
	UPROPERTY(BlueprintReadOnly)	
		bool CanChargeEnergy = true;
	
	UPROPERTY(BlueprintReadOnly)
		float Speed;
	
	UPROPERTY(BlueprintReadOnly)
		float MaxEnergy = 350.f;

	UPROPERTY(BlueprintReadOnly)
		float SaveEnergy;

	UPROPERTY(BlueprintReadOnly)
		float Ratio;

	UPROPERTY(BlueprintReadOnly)
		float Pow;


protected:
	UPROPERTY(BlueprintReadOnly)
		float CurrentEnergy;



};

