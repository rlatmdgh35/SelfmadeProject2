#include "C_BehaviorComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Player/C_Player.h"
#include "Global.h"







AC_Player* UC_BehaviorComponent::GetTargetPlayer()
{
	return Cast<AC_Player>(Blackboard->GetValueAsObject(PlayerKey));
}


void UC_BehaviorComponent::ChangeType(EOfficerType InNewType)
{
	EOfficerType previewType = InNewType;
	Blackboard->SetValueAsEnum(BehaviorKey, (int32)InNewType);



}

FVector UC_BehaviorComponent::GetPlayerLocation()
{
	return Blackboard->GetValueAsVector(LocationKey);
}