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
		
};
