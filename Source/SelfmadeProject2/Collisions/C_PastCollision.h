#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_PastCollision.generated.h"

UCLASS()
class SELFMADEPROJECT2_API AC_PastCollision : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_PastCollision();

private:
	class UBoxComponent* Box;

};
