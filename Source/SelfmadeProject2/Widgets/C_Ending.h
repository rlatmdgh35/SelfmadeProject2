#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Player/C_Player.h"
#include "C_Ending.generated.h"


UCLASS()
class SELFMADEPROJECT2_API UC_Ending : public UUserWidget
{
	GENERATED_BODY()


public:
	void EndingType(EEndingType InType);

private:
	UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* EndingSwitch;

	UPROPERTY(meta = (BindWidget))
		class UWidget* SadEnding;

	UPROPERTY(meta = (BindWidget))
		class UWidget* NormalEnding;

	UPROPERTY(meta = (BindWidget))
		class UWidget* HappyEnding;

	UPROPERTY(meta = (BindWidget))
		class UWidget* HiddenEnding;



};
