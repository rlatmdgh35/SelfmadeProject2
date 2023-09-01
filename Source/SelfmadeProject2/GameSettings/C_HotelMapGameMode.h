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

protected:
	virtual void BeginPlay() override;

private:
	class USkeletalMesh* SkeletalMesh;
	TSubclassOf<class UAnimInstance> AnimClass;
};
