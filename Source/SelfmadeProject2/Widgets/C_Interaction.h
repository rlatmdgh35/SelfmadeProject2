#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Player/C_Player.h"
#include "C_Interaction.generated.h"


UCLASS()
class SELFMADEPROJECT2_API UC_Interaction : public UUserWidget
{
	GENERATED_BODY()


public:
	void BeginPlay(ACharacter* InCharacter);

private:
	UFUNCTION()
		void InteractionText(EInteractionType InType);

private:
	void ClearTextBlock();
	void LightTextBlock();
	void StartOfficerTextBlock();
	void DoorTextBlock();
	void ElevatorTextBlock();
	void LockTextBlock();

public:
	UPROPERTY(BlueprintReadWrite)
		FText OnLightText;

	UPROPERTY(BlueprintReadWrite)
		FText OffLightText;

	UPROPERTY(BlueprintReadWrite)
		FText StartOfficerText;

	UPROPERTY(BlueprintReadWrite)
		FText OpenDoorText;

	UPROPERTY(BlueprintReadWrite)
		FText CloseDoorText;

	UPROPERTY(BlueprintReadWrite)
		FText ElevatorText;

	UPROPERTY(BlueprintReadWrite)
		FText LockText;

private:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MainText;

	class AC_Player* Player;
	class AC_Elevator* Elevator;
	TArray<class AC_LightSwitch*> LightSwitches;
	TArray<class AC_Door*> Doors;
	TArray<class AC_Elevator_Button*> Buttons;

};
