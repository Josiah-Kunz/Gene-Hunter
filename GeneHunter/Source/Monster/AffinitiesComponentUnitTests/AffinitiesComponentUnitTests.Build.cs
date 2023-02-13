using UnrealBuildTool;

public class AffinitiesComponentUnitTests : ModuleRules{
	
	public AffinitiesComponentUnitTests(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.Add("Monster/StatsComponentUnitTests/Private");
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			"Core"						// for FString
		  , "CoreUObject"				// for UObjects (and their initializations)
		  , "Engine"					// for UBlueprintFuncitonLibrary in StatUnitTestUtilities.h
		  , "AffinitiesComponent"		// b/c these are the thing we're testing
		});
	}
}