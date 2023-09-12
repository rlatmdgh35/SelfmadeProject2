#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_Guide.generated.h"


UCLASS()
class SELFMADEPROJECT2_API UC_Guide : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BeginPlay(ACharacter* InCharacter);

protected:
	virtual bool Initialize() override;

public:
	UFUNCTION()
		void ShowFirstPage();

	UFUNCTION()
		void ShowSecondPage();

	UFUNCTION()
		void ShowThirdPage();

public:
	UFUNCTION()
		void OpenEighthGuide();

	UFUNCTION()
		void OpenNinthGuide();

	UFUNCTION()
		void OpenTenthGuide();


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
	class UC_LineOfCharacter* Line;

public:
	UPROPERTY(BlueprintReadWrite)
		FText EighthText;
		/*
		"8. ���� �� ���Ҹ��� ����´ٸ� ��� ���� �͸� \
		�����ÿ�. �츮 ȣ���� �ð����� �����ϴ�.\\";
		*/

	UPROPERTY(BlueprintReadWrite)
		FText NinthText;
		/*
		"9. ���� �� �����Ҹ��� �����Ҹ��� �鸱 ��� \
		�� �Ҹ��� ���� ������ �� �濡 ���� ���� ���ʽÿ�.\\";
		*/

	UPROPERTY(BlueprintReadWrite)
		FText TenthText;
		/*
		"10. ���������͸� Ÿ�� 4������ ���� 404ȣ�� \
		�� �޴� �ͽ� �տ� �����ϴ� ��ȥ���� ��� \
		�ҷ����� ���� �� ���Դϴ�.";
		*/

	UPROPERTY(BlueprintReadWrite)
		FText MosaicEighthText;
		/*
		"8. ���̸��ϵٸڱԱƷٱ䵷�岳������������\
		���级�����޷��ɶڰ����ն�ζݵٷ�˹��츹\\";
		*/

	UPROPERTY(BlueprintReadWrite)
		FText MosaicNinthText;

		/*
		"9. ���̸��ϵٸڱԱƷط��㲳�Ҷ����׸��\
		�͵ٸ׷Ǻ�����ɵ��ɴԲϷѰ��۹淢�ɴְ�\
		���ܹαݷϵٷ����Ʒ״̲з��ݷ��ñƷɶϲ�";
		*/
};
