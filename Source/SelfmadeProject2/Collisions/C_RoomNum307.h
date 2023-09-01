#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_RoomNum307.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOpenEighthGuideSignature);

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

public:
	FOpenEighthGuideSignature OpenEighthGuide;



};
