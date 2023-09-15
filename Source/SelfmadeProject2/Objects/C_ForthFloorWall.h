#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_ForthFloorWall.generated.h"

UCLASS()
class SELFMADEPROJECT2_API AC_ForthFloorWall : public AActor
{
	GENERATED_BODY()
	
public:
	AC_ForthFloorWall();

public:
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
		void DeleteActor();

private:
	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* Wall;

private:
	class AC_Player* Player;

};
