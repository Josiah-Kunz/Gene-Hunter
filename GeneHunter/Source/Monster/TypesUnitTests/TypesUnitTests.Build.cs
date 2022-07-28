using UnrealBuildTool;

public class TypesUnitTests : ModuleRules{
	
	public TypesUnitTests(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.Add("Monster/TypesUnitTests/Private");
		
		PublicDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core", "CoreUObject", "Engine"
			
			// Specifics
			, "UMG"
			
			// Other modules
			, "BPLibraries", "UI", "GHTypes"
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			"Core", "CoreUObject", "Engine", "AITestSuite", "BPLibraries", "GHTypes"
		});
	}
}