#include "C_Log.h"

DEFINE_LOG_CATEGORY_STATIC(GameProject, Warning, All)


void C_Log::Print(int32 InValue, int32 InKey, float InDuration, FColor InColor)
{
	GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, FString::FromInt(InValue));
}

void C_Log::Print(float InValue, int32 InKey, float InDuration, FColor InColor)
{
	GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, FString::SanitizeFloat(InValue));
}

void C_Log::Print(const FString& InValue, int32 InKey, float InDuration, FColor InColor)
{
	GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, InValue);
}

void C_Log::Print(const FVector& InValue, int32 InKey, float InDuration, FColor InColor)
{
	GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, InValue.ToString());
}

void C_Log::Print(const FRotator& InValue, int32 InKey, float InDuration, FColor InColor)
{
	GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, InValue.ToString());
}

void C_Log::Log(int32 InValue)
{
	UE_LOG(GameProject, Warning, L"%d", InValue);
}

void C_Log::Log(float InValue)
{
	UE_LOG(GameProject, Warning, L"%.3f", InValue);
}

void C_Log::Log(const FString& InValue)
{
	UE_LOG(GameProject, Warning, L"%s", *InValue);
}

void C_Log::Log(const FVector& InValue)
{
	UE_LOG(GameProject, Warning, L"%s", *InValue.ToString());
}

void C_Log::Log(const FRotator& InValue)
{
	UE_LOG(GameProject, Warning, L"%s", *InValue.ToString());
}

void C_Log::Log(const UObject* InObject)
{
	FString message;
	if (!!InObject)
		message.Append(InObject->GetName());

	message.Append(!!InObject ? "Is Valid" : "NULL");
	
	UE_LOG(GameProject, Warning, L"%s", *message);
}

void C_Log::Log(const FString& InFuncName, int32 InLineMember)
{
	/*
	FString message;

	message.Append(InFuncName);
	message.Append(", ");
	message.Append(FString::FromInt(InLineMember));

	UE_LOG(GameProject, Warning, L"%s", message);
	*/
}
