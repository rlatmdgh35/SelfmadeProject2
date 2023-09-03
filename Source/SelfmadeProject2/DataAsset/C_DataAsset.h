#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "C_DataAsset.generated.h"

USTRUCT(BlueprintType)
struct FKeepGuide
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		bool First = true;

	UPROPERTY(EditAnywhere)
		bool Second = false;

	UPROPERTY(EditAnywhere)
		bool Third = false;

	UPROPERTY(EditAnywhere)
		bool Fourth = false;

	UPROPERTY(EditAnywhere)
		bool Fifth = false;

	UPROPERTY(EditAnywhere)
		bool Sixth = false;

	UPROPERTY(EditAnywhere)
		bool Seventh = false;

	UPROPERTY(EditAnywhere)
		bool Eighth = false;

	UPROPERTY(EditAnywhere)
		bool Ninth = false;

	UPROPERTY(EditAnywhere)
		bool Tenth = false;
};

USTRUCT(BlueprintType)
struct FOpenGuide
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		bool IsOpenEighth = false;

	UPROPERTY(EditAnywhere)
		bool IsOpenNinth = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool IsOpenTenth = false;
};

UCLASS()
class SELFMADEPROJECT2_API UC_DataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UC_DataAsset();

public:
	void BeginPlay(ACharacter* InOwnerCharacter);




public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "KeepGuide")
		FKeepGuide KeepGuide;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "OpenGiude")
		FOpenGuide OpenGuide;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PlayerState")
		bool IsOpenEyes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PlayerState")
		bool IsCanRun;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Objects")
		bool IsOpenOffice;

private:
	class AC_Player* Player;
	class UC_PlayerComponent* PlayerComponent;

};
