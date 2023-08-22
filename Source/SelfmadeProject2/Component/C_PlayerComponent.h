#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_PlayerComponent.generated.h"


UCLASS()
class SELFMADEPROJECT2_API UC_PlayerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UC_PlayerComponent();
	
public:
	UPROPERTY(EditAnywhere)
		class UC_DataAsset* DataAsset;

private:
	bool OpenEyes;
	float Energy;

public:
	FORCEINLINE bool IsOpenEyes() { return OpenEyes == true; }
	FORCEINLINE bool IsCanRun() { return Energy >= 30.f; }
	FORCEINLINE float GetEnergy() { return Energy; }
};
