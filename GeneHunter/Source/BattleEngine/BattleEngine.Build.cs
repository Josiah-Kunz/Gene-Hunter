﻿using UnrealBuildTool;

public class BattleEngine : ModuleRules{

	public BattleEngine(ReadOnlyTargetRules Target) : base(Target){

		PrivateIncludePaths.AddRange(new string[]{
			"BattleEngine/Private",
		});

		PublicIncludePaths.AddRange(new string[]{
			"BattleEngine/Public",
		});
		
		PublicDependencyModuleNames.AddRange(new string[]{
			"CombatStatsComponent",		// ProjectileData carries this
			"EffectComponent",			// MoveData has EffectsToInflict
			"Engine",					// for ActorComponent.h (external)
			"LevelComponent", 			// CombatStats depend on this
			"Types", 
			"UI",						// MoveData uses FSupportingText
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core",			// for FStrings and such
			"CoreUObject",	// for UObjects
			"BPLibraries",	// for UAssetFunctionLibrary::SortAssetsAlphabetically
			"GHLibraries",	// for REQUIRE_COMPONENT and such
			  
		});
	}
}