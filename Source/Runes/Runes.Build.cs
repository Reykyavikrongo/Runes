// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Runes : ModuleRules
{
	public Runes(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
