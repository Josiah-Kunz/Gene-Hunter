using UnrealBuildTool;

public class CustomSlate : ModuleRules{

	public CustomSlate(ReadOnlyTargetRules Target) : base(Target){
		
		PublicDependencyModuleNames.AddRange(new string[]{ "UMG", "Slate", "SlateCore", "AffinitiesComponent" });

		PrivateIncludePaths.Add("CustomSlate/Private");
		
		PublicIncludePaths.Add("CustomSlate/Public");
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core",			// for basic types
			"CoreUObject",	// to use UObjects
			"Slate", "SlateCore", "UMG", 
			"EditorStyle", // for, e.g., FEditorStyle::Get()
			
			// Other modules
			"BPLibraries", 	// for the WidgetFunctionLibrary
			"Types", 		// for affinity drawers
		}); 
	}
}