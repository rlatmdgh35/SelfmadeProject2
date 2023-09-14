#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "C_BTTaskNode_Run.generated.h"


UCLASS()
class SELFMADEPROJECT2_API UC_BTTaskNode_Run : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UC_BTTaskNode_Run();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	FVector OfficerLocation;
	FVector PlayerLocation;
	float AlphaValue;

};
