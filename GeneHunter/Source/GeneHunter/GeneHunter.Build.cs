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
			
			// Character modules
			"TopdownCharacter",
			
			// Effects modules
			"AuraComponent", "BuffComponent", "DebuffComponent", "DependentEffectComponent", "DoTComponent", 
			"EffectableComponent", "EffectComponent", "EffectComponentUnitTests", 
			"HoTComponent", "IntrinsicEffectComponent", "MutationEffectComponent",
			"NegativeAuraComponent", "PositiveAuraComponent", "TalentEffectComponent", "TimedEffectComponent", 
			"TraitEffectComponent",
			
			// Monster modules
			"AffinitiesComponent", "AffinitiesComponentUnitTests", "CombatStatsComponent", "LevelComponent", "Types",
			
			// Monster unit tests
			"CombatStatsComponentUnitTests", "LevelComponentUnitTests",  "TypesUnitTests",
			  
			// Utility modules
			"BPLibraries", "GHLibraries", "UI",
		});
	}
}
