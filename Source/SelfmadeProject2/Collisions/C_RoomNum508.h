#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_RoomNum508.generated.h"


UCLASS()
class SELFMADEPROJECT2_API AC_RoomNum508 : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_RoomNum508();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;


};
