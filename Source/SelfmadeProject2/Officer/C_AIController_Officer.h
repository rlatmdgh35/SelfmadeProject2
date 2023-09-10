#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "C_AIController_Officer.generated.h"


UCLASS()
class SELFMADEPROJECT2_API AC_AIController_Officer : public AAIController
{
	GENERATED_BODY()
	

public:
	AC_AIController_Officer();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

public:
	float GetSightRadius();

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UC_BehaviorComponent* Behavior;

	UPROPERTY(VisibleDefaultsOnly)
		class UAIPerceptionComponent* Perception;

private:
	class AC_Security_Officer* Officer;
	class UAISenseConfig_Sight* Sight;

};
