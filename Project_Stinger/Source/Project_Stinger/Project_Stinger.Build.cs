// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Project_Stinger : ModuleRules
{
	public Project_Stinger(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
