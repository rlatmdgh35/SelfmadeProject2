#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "C_DataAsset.generated.h"

USTRUCT(BlueprintType)
struct FGuide
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		bool First = false;

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
};

USTRUCT(BlueprintType)
struct FOpenGuide
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		bool IsOpenSeventh = false;

	UPROPERTY(EditAnywhere)
		bool IsOpenEighth = false;

	UPROPERTY(EditAnywhere)
		bool IsOpenNinth = false;

};


UCLASS()
class SELFMADEPROJECT2_API UC_DataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Guide")
		FGuide Guide;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "OpenGiude")
		FOpenGuide OpenGuide;



	
};