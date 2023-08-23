#include "C_PlayerComponent.h"
#include "DataAsset/C_DataAsset.h"
#include "Global.h"



UC_PlayerComponent::UC_PlayerComponent()
{

}

void UC_PlayerComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* ownerCharacter = Cast<ACharacter>(GetOwner());
	DataAsset->BeginPlay(ownerCharacter);


}

