#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_StartCollision.generated.h"


UCLASS()
class SELFMADEPROJECT2_API AC_StartCollision : public AActor
{
	GENERATED_BODY()

public:
	AC_StartCollision();

protected:
	virtual void BeginPlay() override;


private:
	class UBoxComponent* Box;
	class AC_Player* Player;
	FTimerHandle TimerHandle;

private:
	UFUNCTION()
		void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

private:
	void TravelPast();
};