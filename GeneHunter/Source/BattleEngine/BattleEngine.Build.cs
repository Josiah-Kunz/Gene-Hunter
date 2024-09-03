using UnrealBuildTool;

public class BattleEngine : ModuleRules{

	public BattleEngine(ReadOnlyTargetRules Target) : base(Target){

		PrivateIncludePaths.AddRange(new string[]{
			"BattleEngine/Private",
			"BattleEngine/Private/Move",
			"BattleEngine/Private/Projectile",
			"BattleEngine/Private/Projectile/Damage",
			"BattleEngine/Private/Projectile/Direction",
			"BattleEngine/Private/Projectile/EndBehavior",
			"BattleEngine/Private/Projectile/PhysicsInteraction",
			"BattleEngine/Private/Projectile/SpawnSchemes",
			"BattleEngine/Private/Projectile/Targeting",
			
		});

		PublicIncludePaths.AddRange(new string[]{
			"BattleEngine/Public",
			"BattleEngine/Public/Move",
			"BattleEngine/Public/Projectile",
			"BattleEngine/Public/Projectile/Damage",
			"BattleEngine/Public/Projectile/Direction",
			"BattleEngine/Public/Projectile/EndBehavior",
			"BattleEngine/Public/Projectile/PhysicsInteraction",
			"BattleEngine/Public/Projectile/SpawnSchemes",
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