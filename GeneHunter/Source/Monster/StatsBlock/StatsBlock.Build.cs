using UnrealBuildTool;

public class StatsBlock : ModuleRules{

	public StatsBlock(ReadOnlyTargetRules Target) : base(Target){

		PrivateIncludePaths.AddRange(new string[]{
			"Monster/StatsBlock/Private",
			"Monster/StatsBlock/Private/Stats"
		});

		PublicIncludePaths.AddRange(new string[]{
			"Monster/StatsBlock/Public",
			"Monster/StatsBlock/Public/Stats"
		});
		
		PublicDependencyModuleNames.AddRange(new string[]{
			"Engine" // for MathUtil.h (internal) and ActorComponent.h (external)
		  , "UI" // For SupportingText.h
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core"			// for FStrings and such
			, "CoreUObject"	// for UObjects
			  
			// Other modules
			, "BPLibraries" // for Stats using RoundToDecimal
		});
	}
}