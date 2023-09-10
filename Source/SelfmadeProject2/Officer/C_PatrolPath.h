#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_PatrolPath.generated.h"

UCLASS()
class SELFMADEPROJECT2_API AC_PatrolPath : public AActor
{
	GENERATED_BODY()

public:
	AC_PatrolPath();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE class USplineComponent* GetSplineComponent() { return Spline; }

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USplineComponent* Spline;

private:
	UPROPERTY(EditInstanceOnly)
		bool bClosedLoop;
};
