#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_Lock.generated.h"


UCLASS()
class SELFMADEPROJECT2_API UC_Lock : public UUserWidget
{
	GENERATED_BODY()



public:
	void SetTextNum(FText InText);


private:
	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* FirstNum;

	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* SecondNum;

	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* ThirdNum;

	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* ForthNum;

public:
	FText FirstText;
	FText SecondText;
	FText ThirdText;
	FText ForthText;




};
