#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_LightSwitch.generated.h"

UCLASS()
class SELFMADEPROJECT2_API AC_LightSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_LightSwitch();

protected:
	virtual void BeginPlay() override;

public:
	void Interaction();
	void ToggleLight(bool IsOnLight);


public:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* DefaultSceneComponent;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USceneComponent* SwitchRoot;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Switch;

	UPROPERTY(VisibleDefaultsOnly)
		class UPointLightComponent* Light;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Plane1;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Plane2;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Plane3;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Plane4;

	class AC_Player* Player;

	class UStaticMesh* Cube;
	class UMaterial* Material;

public:
	UPROPERTY(EditAnywhere)
		bool bIsOnLight;

	bool bCanCall;

};
