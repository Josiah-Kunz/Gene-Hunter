using UnrealBuildTool;

public class CombatStatsComponent : ModuleRules{

	public CombatStatsComponent(ReadOnlyTargetRules Target) : base(Target){

		PrivateIncludePaths.AddRange(new string[]{
			"Monster/CombatStatsComponent/Private",
			"Monster/CombatStatsComponent/Private/CombatStats"
		});

		PublicIncludePaths.AddRange(new string[]{
			"Monster/CombatStatsComponent/Public",
			"Monster/CombatStatsComponent/Public/CombatStats"
		});
		
		PublicDependencyModuleNames.AddRange(new string[]{
			"BattleEngine",			// To accept MoveData
			"Engine",				// for MathUtil.h (internal) and ActorComponent.h (external)
			"EffectableComponent",	// for effect delegate macros and UEffectableComponent
			"LevelComponent",		// Stats depend on Level
			"UMG",					// For health bar uuserwidget
			"UI",					// for SupportingText.h
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core",			// for FStrings and such
			"CoreUObject",	// for UObjects
			  
			// Other modules
			"AffinitiesComponent",	// For damage calculation
			"BPLibraries",			// for Stats using RoundToDecimal
			"GHLibraries",			// for REQUIRE_COMPONENT macro (since UCombatStatsComponent depends on ULevelComponent)
		});
	}
}