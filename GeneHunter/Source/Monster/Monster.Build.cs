using UnrealBuildTool;

public class Monster : ModuleRules{

	public Monster(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.Add("Monster/Private");
		PrivateIncludePaths.Add("Monster/Private/Types");
		
		PublicIncludePaths.Add("Monster/Public");
		PublicIncludePaths.Add("Monster/Public/Types");
		
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