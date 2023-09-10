#include "C_PatrolComponent.h"
#include "Components/SplineComponent.h"
#include "Officer/C_PatrolPath.h"
#include "Global.h"


UC_PatrolComponent::UC_PatrolComponent()
{
}


void UC_PatrolComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UC_PatrolComponent::NextIndex()
{
	CheckNull(Path);

	int32 count = Path->GetSplineComponent()->GetNumberOfSplinePoints();

	if (Index < count - 1)		Index++;
	else						Index = 0;
}

bool UC_PatrolComponent::GetMoveToLocation(FVector& OutLocation)
{
	OutLocation = FVector::ZeroVector;
	CheckNullResult(Path, false);

	OutLocation = Path->GetSplineComponent()->GetLocationAtSplinePoint(Index, ESplineCoordinateSpace::World);
	return true;
}






