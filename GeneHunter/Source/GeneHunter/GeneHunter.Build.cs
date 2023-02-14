// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GeneHunter : ModuleRules
{
	public GeneHunter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]{
			
			// Basic
			"Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay"
			
			// Modules
			, "AffinitiesComponent", "AffinitiesComponentUnitTests", "BPLibraries", "EffectableComponent", "EffectComponent", "EffectComponentUnitTests", "GHLibraries", "LevelComponent"
			, "StatsComponent", "StatsComponentUnitTests", "Types", "TypesUnitTests", "UI"
		});
	}
}
