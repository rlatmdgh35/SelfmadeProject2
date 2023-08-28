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

	UFUNCTION()
		void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	UFUNCTION(BlueprintImplementableEvent)
		void StartTimeline();

public:
	FORCEINLINE bool IsOverrlaped() { return bOverlapped; }

public:
	void Interaction();


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

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly)
		class USceneComponent* DoorRoot;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USceneComponent* Corner_R;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USceneComponent* Corner_L;


public:
	UPROPERTY(BlueprintReadOnly)
		class AC_Player* Player;

public:
	UPROPERTY(BlueprintReadWrite)
		bool bMoving;

	UPROPERTY(BlueprintReadWrite)
		bool bOpen;

	UPROPERTY(BlueprintReadOnly)
		float Rotation;

	UPROPERTY(BlueprintReadWrite)
		float SaveRotation;

public:
	bool bOverlapped;





};
