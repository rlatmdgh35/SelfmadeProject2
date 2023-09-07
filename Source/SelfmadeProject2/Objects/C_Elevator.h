#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Elevator.generated.h"


UCLASS()
class SELFMADEPROJECT2_API AC_Elevator : public AActor
{
	GENERATED_BODY()

public:
	AC_Elevator();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintImplementableEvent)
		void DoMoveDoor(int32 Type);

	UFUNCTION(BlueprintImplementableEvent)
		void CloseDoor(int32 Type);

protected:
	void ChangeColor();

	UFUNCTION(BlueprintCallable)
		void ResetButtonColor();


public:
	void SetFloor(int32 InFloor);

protected:
	UPROPERTY(BlueprintReadOnly)
		class USceneComponent* RootSceneComponent;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* TopMesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

protected:
	class AC_Player* Player;

private:
	TArray<class AC_Elevator_Button*> Buttons;

public:
	UPROPERTY(BlueprintReadOnly)
		int32 MoveToFloor;

	UPROPERTY(BlueprintReadWrite)
		FVector StartLocation;

	UPROPERTY(BlueprintReadWrite)
		bool bMoving = false;

	UPROPERTY(BlueprintReadWrite)
		bool bCloseDoor = true;

public:
	UPROPERTY(BlueprintReadOnly)
		bool IsOpenTenth = false;


};
