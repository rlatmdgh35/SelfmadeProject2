#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_Guide.generated.h"


UCLASS()
class SELFMADEPROJECT2_API UC_Guide : public UUserWidget
{
	GENERATED_BODY()
	

protected:
	virtual bool Initialize() override;

public:
	UFUNCTION()
		void ShowFirstPage();

	UFUNCTION()
		void ShowSecondPage();

	UFUNCTION()
		void ShowThirdPage();

private:
	UFUNCTION()
		void OpenEighthGuide();

	UFUNCTION()
		void OpenNinthGuide();


private:
	UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* GuidePageSwitcher;

	UPROPERTY(meta = (BindWidget))
		class UWidget* FirstPage;

	UPROPERTY(meta = (BindWidget))
		class UWidget* SecondPage;
	
	UPROPERTY(meta = (BindWidget))
		class UWidget* ThirdPage;

	UPROPERTY(meta = (BindWidget))
		class UButton* ForwardButton_1;

	UPROPERTY(meta = (BindWidget))
		class UButton* ForwardButton_2;

	UPROPERTY(meta = (BindWidget))
		class UButton* BackButton_2;

	UPROPERTY(meta = (BindWidget))
		class UButton* BackButton_3;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Mosaic;

private:
	class AC_RoomNum307* RoomNum307;
	class AC_RoomNum508* RoomNum508;

};
