#pragma once
#include "DetailLayoutBuilder.h"
#include "GHComponentDrawer__BaseClass.h"
#include "PropertyEditor/Public/IDetailCustomization.h"
#include "LevelComponent.h"


class LevelComponentDrawer : public GHComponentDrawer__BaseClass
{

	COMPONENT_SETUP(LevelComponent)

#pragma region Variables

	
private:

	const FString LevelCategoryName = "Level and Experience";


#pragma endregion

#pragma region Boilerplate
	
public:

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

#pragma endregion

#pragma region Private customization functions

private:

	/** Customizes "level" and its bar. */
	virtual void CustomizeLevelDetails(IDetailLayoutBuilder& DetailBuilder);

	/** Customizes "level exp" (exp within the current level). */
	virtual void CustomizeExpDetails(IDetailLayoutBuilder& DetailBuilder);

	/** Customizes cumulative exp. */
	virtual void CustomizeCXPDetails(IDetailLayoutBuilder& DetailBuilder);

#pragma endregion

#pragma region Public utility functions

public:

	/** Checks whether or not it was the user that committed the text via OnEnter or OnUserMovedFocus. */
	static bool UserCommitted(const ETextCommit::Type CommitType);

#pragma endregion
	
};
