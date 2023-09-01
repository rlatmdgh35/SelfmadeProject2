#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_LineOfCharacter.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPastMapSetOffLoopSignature);

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
	FPastMapSetOffLoopSignature PastMapSetOffLoop;

private:
	FTimerDelegate TimerDelegate;

private:
	class UC_Guide* GuideWidget;

private:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* CharacterLineText;

public:
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
