#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "C_BTService_Officer.generated.h"

UCLASS()
class SELFMADEPROJECT2_API UC_BTService_Officer : public UBTService
{
	GENERATED_BODY()

public:
	UC_BTService_Officer();
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


};
