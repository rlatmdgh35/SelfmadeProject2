// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SelfmadeProject2 : ModuleRules
{
	public SelfmadeProject2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "GameplayTasks" });

		PublicIncludePaths.Add(ModuleDirectory);
	}
}
