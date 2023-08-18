#include "C_PastCollision.h"
#include "Components/BoxComponent.h"
#include "Global.h"



AC_PastCollision::AC_PastCollision()
{
	C_Helpers::CreateSceneComponent(this, &Box, "Box");
	Box->SetRelativeScale3D(FVector(15, 3, 5));
	
}



