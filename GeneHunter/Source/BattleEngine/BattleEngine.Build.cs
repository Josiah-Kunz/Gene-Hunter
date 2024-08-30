using UnrealBuildTool;

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
			"EffectableComponent",		// Moveset is effectable
			"EffectComponent",			// MoveData has EffectsToInflict
			"Core",
			"CoreUObject",
			"Engine",					// for ActorComponent.h (external)
			"GameplayTasks",			// for UProjectileMovementComponent
			"LevelComponent", 			// CombatStats depend on this
			"Types", 
			"UI",						// MoveData uses FSupportingText
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core",			// for FStrings and such
			"CoreUObject",	// for UObjects
			"Engine",
			"BPLibraries",	// for UAssetFunctionLibrary::SortAssetsAlphabetically
			"GHLibraries",	// for REQUIRE_COMPONENT and such
			  
		});
	}
}