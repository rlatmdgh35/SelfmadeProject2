#include "C_BTTaskNode_Run.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "C_AIController_Officer.h"
#include "C_Security_Officer.h"
#include "Player/C_Player.h"
#include "Components/C_PlayerComponent.h"
#include "Components/C_BehaviorComponent.h"
#include "Components/C_PatrolComponent.h"
#include "Global.h"


UC_BTTaskNode_Run::UC_BTTaskNode_Run()
{
	NodeName = "Run";

	bNotifyTick = true;
}

EBTNodeResult::Type UC_BTTaskNode_Run::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AC_AIController_Officer* controller = Cast<AC_AIController_Officer>(OwnerComp.GetOwner());
	CheckNullResult(controller, EBTNodeResult::Failed);

	AC_Security_Officer* officer = Cast<AC_Security_Officer>(controller->GetPawn());
	CheckNullResult(officer, EBTNodeResult::Failed);

	UC_BehaviorComponent* behaviorComponent = C_Helpers::GetComponent<UC_BehaviorComponent>(controller);
	CheckNullResult(behaviorComponent, EBTNodeResult::Failed);

	C_Log::Log("Execute");
	OfficerLocation = officer->GetActorLocation();
	PlayerLocation = behaviorComponent->GetPlayerLocation();
	AlphaValue = 0.f;

	return EBTNodeResult::InProgress;
}

void UC_BTTaskNode_Run::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AC_AIController_Officer* controller = Cast<AC_AIController_Officer>(OwnerComp.GetOwner());
	CheckNull(controller);

	AC_Security_Officer* officer = Cast<AC_Security_Officer>(controller->GetPawn());
	CheckNull(officer);

	UC_BehaviorComponent* behaviorComponent = C_Helpers::GetComponent<UC_BehaviorComponent>(controller);
	CheckNull(behaviorComponent);

	AC_Player* player = behaviorComponent->GetTargetPlayer();
	FVector playerLocation = behaviorComponent->GetPlayerLocation();
	
	officer->GetCharacterMovement()->MaxWalkSpeed = 3500.f;

	EPathFollowingRequestResult::Type result = controller->MoveToLocation(playerLocation, 10.f, false);
	if (result == EPathFollowingRequestResult::Failed)
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	if (result == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		if (player->PlayerComponent->IsOpenEyes == true)
		{
			AlphaValue += DeltaSeconds;
			while (true)
			{
				officer->SetActorLocation(UKismetMathLibrary::VLerp(OfficerLocation, PlayerLocation, AlphaValue));
				if (AlphaValue >= 1)	break;
			}
			player->EndingFunction(EEndingType::Sad);
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		}

		else
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}

	officer->GetCharacterMovement()->MaxWalkSpeed = 400.f;
	
}
