using UnrealBuildTool;

public class DetailsPanelArchitect : ModuleRules{

	public DetailsPanelArchitect(ReadOnlyTargetRules Target) : base(Target){

		PublicDependencyModuleNames.AddRange(new string[]{
			"UnrealEd", "DetailCustomizations", "PropertyEditor", "EditorStyle"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			"Core", "CoreUObject", "Engine"
		}); 
		
	}
}