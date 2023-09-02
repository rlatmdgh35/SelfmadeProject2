#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Loop.generated.h"

UCLASS()
class SELFMADEPROJECT2_API AC_Loop : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_Loop();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

// For Show Edior
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

private:
	class AC_Player* Player;

	TSubclassOf<class UC_LineOfCharacter> LineOfCharacterClass;
	class UC_LineOfCharacter* LineOfCharacter;

public:
	bool bLoop = true;

private:
	bool bStart = true;
};
