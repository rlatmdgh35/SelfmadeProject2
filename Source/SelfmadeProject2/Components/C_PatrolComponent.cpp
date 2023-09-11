#include "C_PatrolComponent.h"
#include "Components/SplineComponent.h"
#include "Officer/C_PatrolPath.h"
#include "Officer/C_Security_Officer.h"
#include "Global.h"


UC_PatrolComponent::UC_PatrolComponent()
{
}


void UC_PatrolComponent::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> officerActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_Security_Officer::StaticClass(), officerActor);
	CheckNull(officerActor[0]);
	Officer = Cast<AC_Security_Officer>(officerActor[0]);
}

void UC_PatrolComponent::NextIndex()
{
	CheckNull(Officer);
	CheckNull(Path);
	CheckFalse(Officer->bCanPatrol);

	int32 count = Path->GetSplineComponent()->GetNumberOfSplinePoints();

	if (Index < count - 1)							Index++;
	else if (Officer->bIsJumpScare == false)		Index = 0;
	else											Officer->Destroy();
}

bool UC_PatrolComponent::GetMoveToLocation(FVector& OutLocation)
{
	OutLocation = FVector::ZeroVector;
	CheckNullResult(Path, false);

	OutLocation = Path->GetSplineComponent()->GetLocationAtSplinePoint(Index, ESplineCoordinateSpace::World);
	return true;
}






