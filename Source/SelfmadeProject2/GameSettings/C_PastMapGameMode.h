#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "C_PastMapGameMode.generated.h"


UCLASS()
class SELFMADEPROJECT2_API AC_PastMapGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AC_PastMapGameMode();

protected:
	virtual void BeginPlay() override;
	


};
