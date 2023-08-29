#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Office.generated.h"

UCLASS()
class SELFMADEPROJECT2_API AC_Office : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_Office();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE bool IsOverlapped() { return bOverlapping; }

private:
	UFUNCTION()
		void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
		void EndOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	void Interaction();

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* DefaultSceneComponent;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Door;

	class AC_Player* Player;

private:
	bool bOverlapping = false;


};
