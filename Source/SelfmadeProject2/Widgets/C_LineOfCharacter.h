#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Player/C_Player.h"
#include "C_LineOfCharacter.generated.h"


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
	void PrintHotelMap_3();
	void PrintHotelMap_4();
	void PrintHotelMap_5();
	void PrintHotelMap_6();
	void PrintHotelMap_7();
	void PrintHotelMap_8();
	void PrintHotelMap_9();
	void PrintHotelMap_Eighth();
	void PrintHotelMap_Ninth();
	void PrintHotelMap_Tenth1();
	void PrintHotelMap_Tenth2();

	
	void ClearTextBlock();
	void ClearTextTimer(float InRate, int32 InNum = 0, bool Both = false);


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
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* OtherPersonLineText;

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
	

	UPROPERTY(BlueprintReadWrite)
		FText HotelMap_1;

	UPROPERTY(BlueprintReadWrite)
		FText HotelMap_2;

	UPROPERTY(BlueprintReadWrite)
		FText HotelMap_3;

	UPROPERTY(BlueprintReadWrite)
		FText HotelMap_4;

	UPROPERTY(BlueprintReadWrite)
		FText HotelMap_5;

	UPROPERTY(BlueprintReadWrite)
		FText HotelMap_6;

	UPROPERTY(BlueprintReadWrite)
		FText HotelMap_7;

	UPROPERTY(BlueprintReadWrite)
		FText HotelMap_8;

	UPROPERTY(BlueprintReadWrite)
		FText HotelMap_9;

	UPROPERTY(BlueprintReadWrite)
		FText OpenEighthGuide;

	UPROPERTY(BlueprintReadWrite)
		FText OpenNinthGuide;

	UPROPERTY(BlueprintReadWrite)
		FText OpenTenthGuide1;

	UPROPERTY(BlueprintReadWrite)
		FText OpenTenthGuide2;


private:
	FTimerHandle TimerHandle;
	bool bBoth;

};
