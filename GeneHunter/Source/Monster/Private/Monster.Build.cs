using UnrealBuildTool;

public class Monster : ModuleRules{

	public Monster(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.Add("Monster/Private");
		PublicIncludePaths.Add("Monster/Public");
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core", "CoreUObject", "Engine"
			
			// Other modules
			, "UI"
		}); 
	}
}