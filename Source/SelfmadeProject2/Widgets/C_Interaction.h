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
	void DoorTextBlock();
	void ElevatorTextBlock();
	void LockTextBlock();

public:
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
	TArray<class AC_Door*> Doors;

};
