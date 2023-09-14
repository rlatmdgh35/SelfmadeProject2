#include "C_Security_Officer.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/C_PatrolComponent.h"
#include "Global.h"


AC_Security_Officer::AC_Security_Officer()
{
	C_Helpers::CreateActorComponent(this, &Patrol, "Patrol");
}