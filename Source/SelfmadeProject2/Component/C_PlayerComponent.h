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
	
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
		class UC_DataAsset* DataAsset;

private:
	float Speed;
	float Energy;
	float MaxEnergy = 350.f;

};
