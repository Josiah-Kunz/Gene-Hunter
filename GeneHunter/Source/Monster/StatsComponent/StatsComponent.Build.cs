using UnrealBuildTool;

public class StatsComponent : ModuleRules{

	public StatsComponent(ReadOnlyTargetRules Target) : base(Target){

		PrivateIncludePaths.AddRange(new string[]{
			"Monster/StatsComponent/Private",
			"Monster/StatsComponent/Private/Stats"
		});

		PublicIncludePaths.AddRange(new string[]{
			"Monster/StatsComponent/Public",
			"Monster/StatsComponent/Public/Stats"
		});
		
		PublicDependencyModuleNames.AddRange(new string[]{
			"Engine"	// for MathUtil.h (internal) and ActorComponent.h (external)
		  , "UI"		// For SupportingText.h
		  , "Effects" // For UEffectableComponent
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core"			// for FStrings and such
			, "CoreUObject"	// for UObjects
			  
			// Other modules
			, "BPLibraries"		// for Stats using RoundToDecimal
		});
	}
}