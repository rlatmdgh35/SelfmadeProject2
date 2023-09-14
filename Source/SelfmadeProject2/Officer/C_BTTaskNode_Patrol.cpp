#include "C_BTTaskNode_Patrol.h"
#include "C_AIController_Officer.h"
#include "C_Security_Officer.h"
#include "Components/C_PatrolComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Global.h"



UC_BTTaskNode_Patrol::UC_BTTaskNode_Patrol()
{
	NodeName = "Patrol";

	bNotifyTick = true;
}

EBTNodeResult::Type UC_BTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AC_AIController_Officer* controller = Cast<AC_AIController_Officer>(OwnerComp.GetOwner());
	CheckNullResult(controller, EBTNodeResult::Failed);

	AC_Security_Officer* officer = Cast<AC_Security_Officer>(controller->GetPawn());
	CheckNullResult(officer, EBTNodeResult::Failed);

	UC_PatrolComponent* patrolComponent = C_Helpers::GetComponent<UC_PatrolComponent>(officer);
	CheckNullResult(patrolComponent, EBTNodeResult::Failed);

	return EBTNodeResult::InProgress;
}


EBTNodeResult::Type UC_BTTaskNode_Patrol::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	AC_AIController_Officer* controller = Cast<AC_AIController_Officer>(OwnerComp.GetOwner());
	CheckNullResult(controller, EBTNodeResult::Failed);

	AC_Security_Officer* officer = Cast<AC_Security_Officer>(controller->GetPawn());
	CheckNullResult(officer, EBTNodeResult::Failed);

	officer->GetCharacterMovement()->MaxWalkSpeed = 0.f;

	return EBTNodeResult::Aborted;
}

void UC_BTTaskNode_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AC_AIController_Officer* controller = Cast<AC_AIController_Officer>(OwnerComp.GetOwner());
	CheckNull(controller);

	AC_Security_Officer* officer = Cast<AC_Security_Officer>(controller->GetPawn());
	CheckNull(officer);

	UC_PatrolComponent* patrolComponent = C_Helpers::GetComponent<UC_PatrolComponent>(officer);
	CheckNull(patrolComponent);

	FVector location;
	patrolComponent->GetMoveToLocation(location);

	EPathFollowingRequestResult::Type result = controller->MoveToLocation(location, 20.f, false);

	if (result == EPathFollowingRequestResult::Failed)
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	if (result == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		patrolComponent->NextIndex();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}
