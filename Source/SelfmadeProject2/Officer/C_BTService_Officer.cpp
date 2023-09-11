#include "C_BTService_Officer.h"
#include "C_AIController_Officer.h"
#include "C_Security_Officer.h"
#include "Components/C_BehaviorComponent.h"
#include "Components/C_PatrolComponent.h"
#include "Player/C_Player.h"

#include "Global.h"


UC_BTService_Officer::UC_BTService_Officer()
{
	NodeName = "OfficerService";
}

void UC_BTService_Officer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AC_AIController_Officer* controller = Cast<AC_AIController_Officer>(OwnerComp.GetOwner());
	CheckNull(controller);

	AC_Security_Officer* officer = Cast<AC_Security_Officer>(controller->GetPawn());
	CheckNull(officer);

	UC_BehaviorComponent* behaviorComponent = C_Helpers::GetComponent<UC_BehaviorComponent>(controller);
	CheckNull(behaviorComponent);

	UC_PatrolComponent* patrolComponent = C_Helpers::GetComponent<UC_PatrolComponent>(officer);
	CheckNull(patrolComponent);


	if (officer->bIsJumpScare == true)
	{
		behaviorComponent->ChangeType(EOfficerType::JumpScare);
		return;
	}



	AC_Player* player = behaviorComponent->GetTargetPlayer();
	if (player == nullptr)
	{
		behaviorComponent->ChangeType(EOfficerType::Patrol);
	}

	else
	{
		float distance = officer->GetDistanceTo(player);

		if (distance < controller->GetSightRadius())	behaviorComponent->ChangeType(EOfficerType::Approach);
	}




}
