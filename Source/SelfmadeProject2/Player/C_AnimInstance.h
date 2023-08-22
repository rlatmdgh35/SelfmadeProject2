#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "C_AnimInstance.generated.h"


UCLASS()
class SELFMADEPROJECT2_API UC_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;



protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		float Speed;



};
