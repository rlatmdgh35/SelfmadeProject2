#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_Security_Officer.generated.h"

UCLASS()
class SELFMADEPROJECT2_API AC_Security_Officer : public ACharacter
{
	GENERATED_BODY()

public:
	AC_Security_Officer();

public:
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }
	FORCEINLINE int32 GetTeamID() { return TeamID; }

private:
	UPROPERTY(EditDefaultsOnly)
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleDefaultsOnly)
		class UC_PatrolComponent* Patrol;

	UPROPERTY(EditDefaultsOnly)
		int32 TeamID = 1;



};
