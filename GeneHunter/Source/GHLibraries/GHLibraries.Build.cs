using UnrealBuildTool;

public class GHLibraries : ModuleRules{

	public GHLibraries(ReadOnlyTargetRules Target) : base(Target){
		
		PublicDependencyModuleNames.AddRange(new string[]{
			"NetcodeUnitTest"
		});

		PrivateIncludePaths.Add("GHLibraries/Private");
		
		PublicIncludePaths.Add("GHLibraries/Public");
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			// Basic
			"Core"			// for FStrings (in, e.g., sorting assets)
		  , "CoreUObject"	// for UObjects
		  , "Engine"		// for UBlueprintFunctionLibrary
		});
	}
}