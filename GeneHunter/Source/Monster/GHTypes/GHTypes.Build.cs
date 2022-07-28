using UnrealBuildTool;

public class GHTypes : ModuleRules{

	public GHTypes(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.Add("Monster/GHTypes/Private");
		
		PublicIncludePaths.Add("Monster/GHTypes/Public");
		
		PublicDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core", "CoreUObject", "Engine"
			
			// Specifics
			, "UMG"
			
			// Other modules
			, "BPLibraries", "UI"
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			"AITestSuite", "BPLibraries"
		});
	}
}