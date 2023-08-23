#include "C_DataAsset.h"
#include "GameFramework/Character.h"
#include "Player/C_Player.h"
#include "Component/C_PlayerComponent.h"
#include "Global.h"




UC_DataAsset::UC_DataAsset()
{



}

void UC_DataAsset::BeginPlay(ACharacter* InOwnerCharacter)
{
	Player = Cast<AC_Player>(InOwnerCharacter);
	PlayerComponent = C_Helpers::GetComponent<AC_PlayerComponent>(Player);



}