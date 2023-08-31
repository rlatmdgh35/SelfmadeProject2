#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_Guide.generated.h"


UCLASS()
class SELFMADEPROJECT2_API UC_Guide : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BeginPlay(ACharacter* InCharacter, UWidget* InWidget);

protected:
	virtual bool Initialize() override;

public:
	UFUNCTION()
		void ShowFirstPage();

	UFUNCTION()
		void ShowSecondPage();

	UFUNCTION()
		void ShowThirdPage();

	/*
private:
	UFUNCTION()
		void OpenEighthGuide();

	UFUNCTION()
		void OpenNinthGuide();

	UFUNCTION()
		void OpenTenthGuide();
		*/

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
	class UC_Lock* LockWidget;
	class AC_Player* Player;

private:
	/*
	FString EighthText =
		"8. ¼øÂû Áß Á¾¼Ò¸®°¡ µé·Á¿Â´Ù¸é Áï½Ã ´«°ú ±Í¸¦ \
		¸·À¸½Ã¿À. ¿ì¸® È£ÅÚÀº ½Ã°èÁ¾ÀÌ ¾ø½À´Ï´Ù.\\";
	
	FString NinthText = 
		"9. ¼øÂû Áß ¿ôÀ½¼Ò¸®³ª ¿ïÀ½¼Ò¸®°¡ µé¸± °æ¿ì \
		±× ¼Ò¸®°¡ ¸ØÃâ ¶§±îÁö ±× ¹æ¿¡ Àý´ë µé¾î°¡Áö ¸¶½Ê½Ã¿À.\\";
	
	FString TenthText =
		"10. ¿¤¸®º£ÀÌÅÍ¸¦ Å¸°í 4ÃþÀ¸·Î °¡¼­ 404È£¿¡ \
		¸ñ ¸Þ´Ü ±Í½Å ¾Õ¿¡ ½½ÆÛÇÏ´Â ¿µÈ¥µéÀ» ¸ðµÎ \
		ºÒ·¯¿À¸é ¼ººÒ µÉ °ÍÀÔ´Ï´Ù.";

	FString MosaicEighthText =
		"8. º§±Ì¸ì±ó·ÏµÙ¸Ú±Ô±Æ·Ù±äµ·µå²³·ø·»¹ý¸¹°©¶»\
		·÷±çº§´³¶§¹Þ·¢·É¶Ú°Áº§¶Õ¶è±Î¶ÝµÙ·ñ±Ë¹ý¸ì¸¹\\";

	FString MosaicNinthText =
		"9. º§±Ì¸ì±ó·ÏµÙ¸Ú±Ô±Æ·Ø·ïºá¶ã²³¸Ò¶ùº£¶×¸ë¹Õ\
		¶ÍµÙ¸×·Çº§µ£¸ì±Éµþ·É´Ô²Ï·Ñ°£°Û¹æ·¢·É´Ö°Á\
		¹ý¸Ü¹Î±Ý·ÏµÙ·¼º­±Æ·×´Ì²Ð·©·Ý·»±Ã±Æ·É¶Ï²Ñ";
	*/

};
