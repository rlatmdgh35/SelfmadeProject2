#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_PatrolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SELFMADEPROJECT2_API UC_PatrolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UC_PatrolComponent();

protected:
	virtual void BeginPlay() override;

public:
	void NextIndex();
	bool GetMoveToLocation(FVector& OutLocation);


private:
	UPROPERTY(EditAnywhere)
		class AC_PatrolPath* Path;

	UPROPERTY(EditAnywhere)
		int32 Index;
		
};
