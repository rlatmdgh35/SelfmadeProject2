#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_LockActor.generated.h"

UCLASS()
class SELFMADEPROJECT2_API AC_LockActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_LockActor();

protected:
	virtual void BeginPlay() override;

public:
	void Interaction();

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* LockMesh;

	class AC_Player* Player;

public:
	UPROPERTY(BlueprintReadWrite)
		bool bLookAtMe = false;



};
