﻿using UnrealBuildTool;

public class DoTComponent : ModuleRules{

	public DoTComponent(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.AddRange(new string[]{
			"EffectComponentModules/DoTComponent/Private",
			"EffectComponentModules/DoTComponent/Private/DoTs",
		});

		PublicIncludePaths.AddRange(new string[]{
			"EffectComponentModules/DoTComponent/Public",
			"EffectComponentModules/DoTComponent/Public/DoTs",
		});
		
		PublicDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core",        // for IMPLEMENT_MODULE
			"CoreUObject", // for UObjects
			"Engine",      // for AActor
			
			// Libraries and utilities
			"BPLibraries",			// for SplitCamelCase
			"BuffComponent",		// for inheritance
			"CombatStatsComponent",	// because we're healing the FHealth over time
			"EffectComponent",		// for inheritance
			"GHLibraries",			// for component utilities SEARCH_FOR_COMPONENT
			"TimedEffectComponent",	// for inheritance
			"UI",					// for SupportingText
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
		});
	}
}