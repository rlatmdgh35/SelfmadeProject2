#include "C_AnimInstance.h"

#include "Global.h"


void UC_AnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();



}

void UC_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* ownerPawn = TryGetPawnOwner();
	CheckNull(ownerPawn);

	Speed = ownerPawn->GetVelocity().Size2D();

}