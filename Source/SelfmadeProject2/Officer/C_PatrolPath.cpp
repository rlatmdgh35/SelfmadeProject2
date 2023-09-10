#include "C_PatrolPath.h"
#include "Components/SplineComponent.h"
#include "Global.h"




AC_PatrolPath::AC_PatrolPath()
{
	C_Helpers::CreateSceneComponent(this, &Spline, "Spline", RootComponent);

	Spline->SetClosedLoop(false);
}

void AC_PatrolPath::BeginPlay()
{
	Super::BeginPlay();
	
}


