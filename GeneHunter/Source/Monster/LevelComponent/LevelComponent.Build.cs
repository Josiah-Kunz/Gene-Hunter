using UnrealBuildTool;

public class LevelComponent : ModuleRules{

	public LevelComponent(ReadOnlyTargetRules Target) : base(Target){

		PrivateIncludePaths.AddRange(new string[]{
			"Monster/LevelComponent/Private",
		});

		PublicIncludePaths.AddRange(new string[]{
			"Monster/LevelComponent/Public",
		});
		
		PublicDependencyModuleNames.AddRange(new string[]{
			"Engine"	// for MathUtil.h (internal) and ActorComponent.h (external)
		  , "UI"		// for SupportingText.h
		  , "EffectableComponent"		// for effect delegate macros and UEffectableComponent
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