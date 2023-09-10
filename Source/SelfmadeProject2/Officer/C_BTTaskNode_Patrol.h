#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "C_BTTaskNode_Patrol.generated.h"



UCLASS()
class SELFMADEPROJECT2_API UC_BTTaskNode_Patrol : public UBTTaskNode
{
	GENERATED_BODY()
	

public:
	UC_BTTaskNode_Patrol();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere)
		float AcceptanceRadius = 20.f;

};
