#pragma once
#include "DetailLayoutBuilder.h"
#include "PropertyEditor/Public/IDetailCustomization.h"
#include "AffinitiesComponent.h"
#include "TypeArray1D.h"


class IAffinitiesComponentDrawer : public IDetailCustomization
{

#pragma region Variables

private:
	
	UAffinitiesComponent* AffinitiesComponent = nullptr;

	TArray<UType*> AllTypes;
	TArray<TSharedPtr<FString>> TypeNames;


#pragma endregion

#pragma region Boilerplate
	
public:

	static TSharedRef<IDetailCustomization> MakeInstance();

	/**
	 * Where the magic happens!
	 */
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:

	TArray<TWeakObjectPtr<UObject>> ObjectsToEdit;

#pragma endregion

#pragma region Affinities category customization functions

	/**
	 * Responsible for the entire "Affinities" category.
	 */
	virtual void CustomizeAffinitiesCategory(IDetailLayoutBuilder& DetailBuilder,
		const TSharedRef<IPropertyHandle> PropertyHandle);

	/**
	 * Customizes the simple private variable that determines how many "Types" a Monster may have (e.g., dual Type).
	 * Necessary since this variable is only accessible via setter and getter functions.
	 */
	virtual void CustomizeMaxUsableAffinities(IDetailLayoutBuilder& DetailBuilder, IDetailCategoryBuilder& Category);

	/**
	 * Customizes the affinities available to the Monster.
	 */
	virtual void CustomizeAffinities(IDetailLayoutBuilder& DetailBuilder, IDetailCategoryBuilder& Category);

	/**
	 * Draws a single affinity row by using SAffinity slate.
	 */
	virtual void DrawAffinity(IDetailLayoutBuilder& DetailBuilder, IDetailCategoryBuilder& Category,
		FAffinity& Affinity);
	
	/**
	 * Draws the +/-/trash buttons for modifying the array of affinities.
	 */
	virtual void DrawArrayMutator(IDetailLayoutBuilder& DetailBuilder, IDetailCategoryBuilder& Category);

#pragma endregion

#pragma region Combat profile category customization functions

	/**
	 * Draws the attack and defense profile categories based on the allocated affinities' types.
	 */
	virtual void CustomizeCombatProfileCategories(IDetailLayoutBuilder& DetailBuilder,
			const TSharedRef<IPropertyHandle> PropertyHandle);

	/**
	 * Generic profile drawer for "attack" or "defense".
	 */
	virtual void DrawCombatProfile(IDetailLayoutBuilder& DetailBuilder, IDetailCategoryBuilder& Category,
		TArray<UType*>& AffinityTypes, const bool bAtk);

#pragma endregion

#pragma region Public utility functions

public:

	/**
	 * Marks the current object as dirty and refreshes the detail builder.
	 */
	void SaveAndRefresh(IDetailLayoutBuilder& DetailBuilder) const;

	/**
	 * To be used with the ComboBox's FString values.
	 */
	UType* GetTypeByName(const FString* TypeName);

	/**
	 * Function called when the ComboBox has changed.
	 */
	TFunction<void(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo)> OnComboBoxChanged(
		IDetailLayoutBuilder& DetailBuilder, FAffinity& Affinity);

#pragma endregion

#pragma region Private utility functions
	
private:

	/**
	 * Retrieves the star of the show!
	 */ 
	UAffinitiesComponent* GetAffinitiesComponent(const IDetailLayoutBuilder& DetailBuilder);

	/**
	 * Gets the category from the passed DetailBuilder.
	 */
	IDetailCategoryBuilder& GetCategory(IDetailLayoutBuilder& DetailBuilder, const FString CategoryName) const;

	/**
	 * A safe and fast way to get all UTypes.
	 */
	TArray<UType*> GetAllTypes();

	/**
	 * Creates the delegate that fires when the reset button is clicked on an affinity.
	 */
	FSimpleDelegate AffinityResetDelegate(IDetailLayoutBuilder& DetailBuilder, FAffinity& Affinity) const;

	/**
	 * Determines the enabled state of the SAffinity.
	 */
	bool CanModifyAffinity(const FAffinity& Affinity) const;

#pragma endregion
	
};
