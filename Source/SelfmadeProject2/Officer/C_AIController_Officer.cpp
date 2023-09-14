#include "C_AIController_Officer.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Officer/C_Security_Officer.h"
#include "Player/C_Player.h"
#include "Components/C_PlayerComponent.h"
#include "Components/C_BehaviorComponent.h"
#include "Global.h"



AC_AIController_Officer::AC_AIController_Officer()
{
	C_Helpers::CreateActorComponent(this, &Blackboard, "Blackboard");
	C_Helpers::CreateActorComponent(this, &Behavior, "Behavior");
	C_Helpers::CreateActorComponent(this, &Perception, "Perception");
	C_Helpers::CreateActorComponent(this, &Sight, "Sight");

	Sight->SightRadius = 1000.f;
	Sight->LoseSightRadius = 1000.f;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = true;

	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(Sight->GetSenseImplementation());
}

void AC_AIController_Officer::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Officer = Cast<AC_Security_Officer>(InPawn);
	CheckNull(Officer);

	UseBlackboard(Officer->GetBehaviorTree()->BlackboardAsset, Blackboard);
	Behavior->SetBlackboard(Blackboard);

	RunBehaviorTree(Officer->GetBehaviorTree());

	Perception->OnPerceptionUpdated.AddDynamic(this, &AC_AIController_Officer::OnPerceptionUpdated);
}

void AC_AIController_Officer::OnUnPossess()
{
	Super::OnUnPossess();

	Perception->OnPerceptionUpdated.Clear();
}

void AC_AIController_Officer::BeginPlay()
{
	Super::BeginPlay();
}

void AC_AIController_Officer::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	TArray<AActor*> perceivedActors;
	Perception->GetCurrentlyPerceivedActors(nullptr, perceivedActors);

	AC_Player* player = nullptr;
	for (const auto& perceivedActor : perceivedActors)
	{
		player = Cast<AC_Player>(perceivedActor);

		if (player != nullptr)
		{
			Blackboard->SetValueAsObject("PlayerKey", player);
			Blackboard->SetValueAsVector("LocationKey", player->GetActorLocation());

			break;
		}
	}

	Blackboard->SetValueAsObject("PlayerKey", player);
}

float AC_AIController_Officer::GetSightRadius()
{
	return Sight->SightRadius;
}


