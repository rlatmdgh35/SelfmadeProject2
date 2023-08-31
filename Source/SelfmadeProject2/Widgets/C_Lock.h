#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_Lock.generated.h"


UCLASS()
class SELFMADEPROJECT2_API UC_Lock : public UUserWidget
{
	GENERATED_BODY()

public:
	void BeginPlay(ACharacter* InCharacter);

public:
	void PressBackSpace();

private:
	bool CheckLockNum();
	void ClearNum();

	UFUNCTION()
		void Quit();

public:
	void SetTextNum(FText InText);



private:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* FirstNum;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* SecondNum;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ThirdNum;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ForthNum;

	UPROPERTY(meta = (BindWidget))
		class UButton* QuitButton;

private:
	class AC_Player* Player;

public:
	FText FirstText;
	FText SecondText;
	FText ThirdText;
	FText ForthText;

private:
	int32 Index = 1;


};
