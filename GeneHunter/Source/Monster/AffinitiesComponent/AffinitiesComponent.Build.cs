using UnrealBuildTool;

public class AffinitiesComponent : ModuleRules{

	public AffinitiesComponent(ReadOnlyTargetRules Target) : base(Target){

		PrivateIncludePaths.AddRange(new string[]{
			"Monster/AffinitiesComponent/Private",
			"Monster/AffinitiesComponent/Public",
		});

		PublicIncludePaths.AddRange(new string[]{
			"Monster/AffinitiesComponent/Public",
			"Monster/AffinitiesComponent/Private",
		});
		
		PublicDependencyModuleNames.AddRange(new string[]{
			"Engine"	// for MathUtil.h (internal) and ActorComponent.h (external)
			, "Types"	// because that's what affinities are
			, "Effects" // For UEffectableComponent
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core",			// for FStrings and such
			"CoreUObject",	// for UObjects
			"EditorStyle",	// for, e.g., FEditorStyle::Get()
			"Slate",		// for SButton
			"SlateCore",	// for SCompoundWidget
			  
			// Other modules
		});
	}
}