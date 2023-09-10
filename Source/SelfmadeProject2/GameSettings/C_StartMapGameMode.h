#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "C_StartMapGameMode.generated.h"


UCLASS()
class SELFMADEPROJECT2_API AC_StartMapGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AC_StartMapGameMode();

protected:
	virtual void BeginPlay() override;

};
