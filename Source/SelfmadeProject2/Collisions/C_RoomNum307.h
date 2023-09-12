#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_RoomNum307.generated.h"


UCLASS()
class SELFMADEPROJECT2_API AC_RoomNum307 : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_RoomNum307();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);


private:
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;




};
