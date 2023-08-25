#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Door.generated.h"



UCLASS()
class SELFMADEPROJECT2_API AC_Door : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_Door();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	UFUNCTION(BlueprintImplementableEvent)
		void StartTimeline();


private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* DefaultSceneComponent;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* DoorHandle_F;
	
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* DoorHandle_B;
	
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

public:
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly)
		class UStaticMeshComponent* Door;


public:
	UPROPERTY(BlueprintReadOnly)
		class AC_Player* Player;

public:
	UPROPERTY(BlueprintReadWrite)
		bool bClosing;

	UPROPERTY(BlueprintReadWrite)
		bool bOpen;

	UPROPERTY(BlueprintReadOnly)
		float Rotation;

	UPROPERTY(BlueprintReadWrite)
		float SaveRotation;



};
