using UnrealBuildTool;

public class UI : ModuleRules{

	public UI(ReadOnlyTargetRules Target) : base(Target){
		
		PublicDependencyModuleNames.AddRange(new string[]{ "UMG", "Slate", "SlateCore" });

		PrivateIncludePaths.Add("UI/Private");
		
		PublicIncludePaths.Add("UI/Public");
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core",			// for basic types
			"CoreUObject"	// fe use UObjects
			
			// All for Rama
			, "AppFramework", "Slate", "SlateCore", "UMG"
			
			// Other modules
			, "BPLibraries"	// for the WidgetFunctionLibrary
		}); 
	}
}