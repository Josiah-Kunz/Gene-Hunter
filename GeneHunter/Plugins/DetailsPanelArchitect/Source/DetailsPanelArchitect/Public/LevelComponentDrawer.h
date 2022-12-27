#pragma once
#include "DetailLayoutBuilder.h"
#include "PropertyEditor/Public/IDetailCustomization.h"
#include "LevelComponent.h"


class LevelComponentDrawer : public IDetailCustomization
{

#pragma region Variables

	
private:
	ULevelComponent* LevelComponent = nullptr;

	const FString LevelCategoryName = "Level";


#pragma endregion

#pragma region Boilerplate
	
public:

	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:

	TArray<TWeakObjectPtr<UObject>> ObjectsToEdit;

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

	/** Marks the LevelComponent as dirty via transaction and refreshes the entire DetailBuilder. */
	void SaveAndRefresh(IDetailLayoutBuilder& DetailBuilder) const;

	/** Checks whether or not it was the user that committed the text via OnEnter or OnUserMovedFocus. */
	static bool UserCommitted(const ETextCommit::Type CommitType);

#pragma endregion

#pragma region Private utility functions
	
private:

	/** Retrieves the current LevelComponent that is being edited. Could be nullptr. */
	ULevelComponent* GetLevelComponent(const IDetailLayoutBuilder& DetailBuilder);
	
	/** Converts the value to FText depending on whether or not its an integer. */
	static FText FloatToFText(const float Value, const bool bIntegerOnly);

#pragma endregion
	
};
