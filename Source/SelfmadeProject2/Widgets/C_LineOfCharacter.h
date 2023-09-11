#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Player/C_Player.h"
#include "C_LineOfCharacter.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlaySoundCharacterLine, ECharacterLineType, InType);

UCLASS()
class SELFMADEPROJECT2_API UC_LineOfCharacter : public UUserWidget
{
	GENERATED_BODY()

public:
	void BeginPlay(ACharacter* InCharacter);


public:
	UFUNCTION()
		void SetCharacterLine(ECharacterLineType InType);

// LineOfCharacter Functions
private:
	void PrintStartMap_1();
	void PrintStartMap_2();
	void PrintStartMap_3();
	void PrintStartMap_4();
	void PrintStartMap_5();
	void PrintStartMap_6();
	void PrintStartMap_7();

	void PrintPastMap_1();
	void PrintPastMap_2();
	void PrintPastMap_3();
	void PrintPastMap_4();
	void PrintPastMap_5();

	void PrintHotelMap_1();
	void PrintHotelMap_2();



	void PrintEighthGuide();
	void PrintNinthGuide();
	void PrintTenthGuide();



	void ClearTextBlock();

public:
	FPlaySoundCharacterLine PlaySoundCharacterLine;

private:
	FTimerDelegate TimerDelegate;

private:
	class AC_Player* Player;
	class UC_Guide* GuideWidget;
	class AC_Loop* Loop;

private:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* CharacterLineText;

public:
	UPROPERTY(BlueprintReadWrite)
		FText StartMap_1;

	UPROPERTY(BlueprintReadWrite)
		FText StartMap_2;

	UPROPERTY(BlueprintReadWrite)
		FText StartMap_3;

	UPROPERTY(BlueprintReadWrite)
		FText StartMap_4;

	UPROPERTY(BlueprintReadWrite)
		FText StartMap_5;

	UPROPERTY(BlueprintReadWrite)
		FText StartMap_6;

	UPROPERTY(BlueprintReadWrite)
		FText StartMap_7;


	UPROPERTY(BlueprintReadWrite)
		FText PastMap_1;

	UPROPERTY(BlueprintReadWrite)
		FText PastMap_2;

	UPROPERTY(BlueprintReadWrite)
		FText PastMap_3;

	UPROPERTY(BlueprintReadWrite)
		FText PastMap_4;

	UPROPERTY(BlueprintReadWrite)
		FText PastMap_5;

	/*
	UPROPERTY(BlueprintReadWrite)
		FText ;

	UPROPERTY(BlueprintReadWrite)
		FText;

	UPROPERTY(BlueprintReadWrite)
		FText;

	UPROPERTY(BlueprintReadWrite)
		FText;

	UPROPERTY(BlueprintReadWrite)
		FText;

	UPROPERTY(BlueprintReadWrite)
		FText;

	UPROPERTY(BlueprintReadWrite)
		FText ;
		*/

	UPROPERTY(BlueprintReadWrite)
		FText OpenEighthGuide;

private:
	FTimerHandle TimerHandle;

};
