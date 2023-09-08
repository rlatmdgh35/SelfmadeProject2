#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Objects/C_Elevator.h"
#include "C_Elevator_OutDoor.generated.h"


UCLASS()
class SELFMADEPROJECT2_API AC_Elevator_OutDoor : public AActor
{
	GENERATED_BODY()

public:
	AC_Elevator_OutDoor();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* DefaultSceneComponent;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UStaticMeshComponent* RightDoor;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UStaticMeshComponent* LeftDoor;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

private:
	TArray<class AC_Elevator_Button*> Buttons;

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		int32 Floor;

public:
	UPROPERTY(BlueprintReadOnly)
		FVector Location_R;

	UPROPERTY(BlueprintReadOnly)
		FVector Location_L;


	
};
