#pragma once
#include "DetailLayoutBuilder.h"
#include "PropertyEditor/Public/IDetailCustomization.h"
#include "AffinitiesComponent.h"
#include "TypeArray1D.h"
#include "Widgets/SCanvas.h"


class AffinitiesComponentDrawer : public IDetailCustomization
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
	 * Draws a single affinity row.
	 */
	virtual void DrawAffinity(IDetailLayoutBuilder& DetailBuilder, IDetailCategoryBuilder& Category,
		FAffinity& Affinity);

	/**
	 * Draws the "value" side of a single affinity row.
	 */
	TSharedPtr<SHorizontalBox> AffinityValueWidget(IDetailLayoutBuilder& DetailBuilder, FAffinity& Affinity) const;

	/**
	 * Draws the +/-/trash buttons for modifying the array of affinities.
	 */
	virtual void DrawArrayMutator(IDetailLayoutBuilder& DetailBuilder, IDetailCategoryBuilder& Category);

#pragma endregion

#pragma region Combat profile category customization functions
	
	virtual void CustomizeCombatProfileCategories(IDetailLayoutBuilder& DetailBuilder,
			const TSharedRef<IPropertyHandle> PropertyHandle);

	virtual void DrawCombatProfile(IDetailLayoutBuilder& DetailBuilder, IDetailCategoryBuilder& Category,
		TArray<UType*>& AffinityTypes, const bool bAtk);

	virtual TSharedRef<SWidget> MakeTypeRowWidget(TArray<FTypeArray1D>& Analysis, 
			const int ArrayIndex, const float Width=80, const float Height=20, const float CornerRadius=4);

	virtual void NoCombatProfile(IDetailCategoryBuilder& Category);

#pragma endregion

#pragma region Public utility functions

public:
	
	void SaveAndRefresh(IDetailLayoutBuilder& DetailBuilder) const;

	static bool UserCommitted(const ETextCommit::Type CommitType);

	UType* GetTypeByName(const FString* TypeName);

	TFunction<void(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo)> OnComboBoxChanged(
		IDetailLayoutBuilder& DetailBuilder, FAffinity& Affinity);

#pragma endregion

#pragma region Private utility functions
	
private:
	
	UAffinitiesComponent* GetAffinitiesComponent(const IDetailLayoutBuilder& DetailBuilder);

	IDetailCategoryBuilder& GetCategory(IDetailLayoutBuilder& DetailBuilder, const FString CategoryName);
	
	// Do we need this??
	TArray<TSharedPtr<UType*, ESPMode::ThreadSafe>> GetTypes() const;

	TArray<TSharedPtr<FString, ESPMode::ThreadSafe>> GetTypeNames();

	FSimpleDelegate CreateResetDelegate(IDetailLayoutBuilder& DetailBuilder, FAffinity& Affinity) const;

	bool CanModifyAffinity(const FAffinity& Affinity) const;

#pragma endregion
	
};
