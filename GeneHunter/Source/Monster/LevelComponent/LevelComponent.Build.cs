using UnrealBuildTool;

public class LevelComponent : ModuleRules{

	public LevelComponent(ReadOnlyTargetRules Target) : base(Target){

		PrivateIncludePaths.AddRange(new string[]{
			"Monster/LevelComponent/Private",
			"Monster/LevelComponent/Private/Stats"
		});

		PublicIncludePaths.AddRange(new string[]{
			"Monster/LevelComponent/Public",
			"Monster/LevelComponent/Public/Stats"
		});
		
		PublicDependencyModuleNames.AddRange(new string[]{
			"Engine"	// for MathUtil.h (internal) and ActorComponent.h (external)
		  , "UI"		// for SupportingText.h
		  , "Effects"	// for UEffectableComponent
		  , "BPLibraries"		// for effect delegate macros
		  , "LevelComponent"	// Stats depend on Level
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