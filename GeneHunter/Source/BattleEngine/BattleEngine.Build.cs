using UnrealBuildTool;

public class BattleEngine : ModuleRules{

	public BattleEngine(ReadOnlyTargetRules Target) : base(Target){

		PrivateIncludePaths.AddRange(new string[]{
			"BattleEngine/Private",
			"BattleEngine/Private/Move",
			"BattleEngine/Private/Move/SpawnSchemes",
			"BattleEngine/Private/Move/UsabilitySchemes",
			"BattleEngine/Private/Projectile",
			"BattleEngine/Private/Projectile/Damage",
			"BattleEngine/Private/Projectile/Direction",
			"BattleEngine/Private/Projectile/Speed",
			"BattleEngine/Private/Projectile/Targeting",
			
		});

		PublicIncludePaths.AddRange(new string[]{
			"BattleEngine/Public",
			"BattleEngine/Public/Move",
			"BattleEngine/Public/Move/SpawnSchemes",
			"BattleEngine/Public/Move/UsabilitySchemes",
			"BattleEngine/Public/Outlets",
			"BattleEngine/Public/Projectile",
			"BattleEngine/Public/Projectile/Damage",
			"BattleEngine/Public/Projectile/Direction",
			"BattleEngine/Public/Projectile/Speed",
			"BattleEngine/Public/Projectile/Targeting",
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
			"TopdownCharacter",			// Need access to the HUD
			"Types", 
			"UI", 						// MoveData uses FSupportingText
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core",			// for FStrings and such
			"CoreUObject",	// for UObjects
			"Engine",		// for FHitResult (if nothing else?)
			"BPLibraries",	// for UAssetFunctionLibrary::SortAssetsAlphabetically
			"GHLibraries",	// for REQUIRE_COMPONENT and such
			  
		});
	}
}