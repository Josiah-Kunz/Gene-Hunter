using UnrealBuildTool;

public class UI : ModuleRules{

	public UI(ReadOnlyTargetRules Target) : base(Target){
		PublicDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core", "CoreUObject", "Engine"
			
			// Specifics
			, "AppFramework", "Slate", "SlateCore", "BPLibraries", "UMG"
		}); 
	}
}