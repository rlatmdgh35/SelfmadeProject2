#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_BehaviorComponent.generated.h"


UENUM(BlueprintType)
enum class EOfficerType : uint8
{
	 Patrol, Approach, JumpScare
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SELFMADEPROJECT2_API UC_BehaviorComponent : public UActorComponent
{
	GENERATED_BODY()
		

public:
	void ChangeType(EOfficerType InNewType);

public:
	FORCEINLINE void SetBlackboard(class UBlackboardComponent* InBlackboard) { Blackboard = InBlackboard; }

	FVector GetPlayerLocation();

public:
	class AC_Player* GetTargetPlayer();

private:
	class UBlackboardComponent* Blackboard;

public:
	UPROPERTY(BlueprintReadOnly)
		EOfficerType OfficerType;

private:
	UPROPERTY(EditAnywhere)
		FName BehaviorKey = "BehaviorKey";

	UPROPERTY(EditAnywhere)
		FName PlayerKey = "PlayerKey";

	UPROPERTY(EditAnywhere)
		FName LocationKey = "LocationKey";


};
