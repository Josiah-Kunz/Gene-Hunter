using UnrealBuildTool;

public class TypesUnitTests : ModuleRules{
	
	public TypesUnitTests(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.Add("Monster/TypesUnitTests/Private");
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			"Core", "CoreUObject", "Engine", "BPLibraries", "Types"
		});
	}
}