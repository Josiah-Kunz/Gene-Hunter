// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GeneHunter : ModuleRules
{
	public GeneHunter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]{
			
			// Basic
			"Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay",
			
			// Effects modules
			"AuraComponent", "BuffComponent", "DebuffComponent", "DoTComponent", "EffectableComponent", "EffectComponent", 
			"EffectComponentUnitTests", 
			"HoTComponent", "IntrinsicEffectComponent", "MutationComponent",
			"NegativeAuraComponent", "PositiveAuraComponent", "TimedEffectComponent", "TraitComponent",
			
			// Monster modules
			"AffinitiesComponent", "AffinitiesComponentUnitTests", "CombatStatsComponent", "LevelComponent",
			"LevelComponentUnitTests",
			"StatsComponentUnitTests", "Types", "TypesUnitTests", 
			  
			// Utility modules
			"BPLibraries", "GHLibraries", "UI",
		});
	}
}
