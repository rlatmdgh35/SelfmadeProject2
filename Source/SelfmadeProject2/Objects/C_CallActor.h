#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_CallActor.generated.h"

UCLASS()
class SELFMADEPROJECT2_API AC_CallActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_CallActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
