#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "C_HotelMapGameMode.generated.h"


UCLASS()
class SELFMADEPROJECT2_API AC_HotelMapGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AC_HotelMapGameMode();

public: 
	virtual void BeginPlay() override;


};
