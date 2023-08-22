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

protected:
	virtual void BeginPlay() override;


private:
	class UBoxComponent* Box;
	FTimerHandle TimerHandle;

private:
	UFUNCTION()
		void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

private:
	void TravelHotel();




};
