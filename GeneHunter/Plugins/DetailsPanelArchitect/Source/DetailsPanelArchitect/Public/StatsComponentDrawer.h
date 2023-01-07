#pragma once
#include "DetailLayoutBuilder.h"
#include "PropertyEditor/Public/IDetailCustomization.h"
#include "StatsComponent.h"


class StatsComponentDrawer : public IDetailCustomization
{

#pragma region Variables

public:
	inline constexpr static float Padding = 2;
	inline constexpr static float StatInputWidth = 50;
	inline constexpr static float StatAbbrevMaxWidth = 30;
	inline constexpr static float SlashWidth = 10;
	inline constexpr static float ValueMaxWidth = 125;
	inline constexpr static float MaxHeight = 20;
	inline constexpr static int SigFigs = 3;

private:
	UStatsComponent* StatsComponent = nullptr;


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

	/** Customizes current and permanent stats. */
	virtual void CustomizeCurrentStatsDetails(IDetailLayoutBuilder& DetailBuilder);

	/** Customizes base stats. */
	virtual void CustomizeBaseStatsDetails(IDetailLayoutBuilder& DetailBuilder);

	/** Customizes base pairs. */
	virtual void CustomizeBasePairsDetails(IDetailLayoutBuilder& DetailBuilder);

#pragma endregion

#pragma region Public utility functions

public:

	/** Marks the StatsComponent as dirty via transaction and refreshes the entire DetailBuilder. */
	void SaveAndRefresh(IDetailLayoutBuilder& DetailBuilder) const;

	/** Creates the delegate for when the EditableTextBox is committed depending on the StatValueType
	 * (current, base stat, etc.). */
	TFunction<void(const FText&, ETextCommit::Type&)> StatOnTextCommitted(
		IDetailLayoutBuilder& DetailBuilder, const EStatEnum TargetStat,
		const EStatValueType StatValueType, const bool bPercentage) const;

	/** Checks whether or not it was the user that committed the text via OnEnter or OnUserMovedFocus. */
	static bool UserCommitted(const ETextCommit::Type CommitType);

#pragma endregion

#pragma region Private utility functions
	
private:

	/** Retrieves the current StatsComponent that is being edited. Could be nullptr. */
	UStatsComponent* GetStatsComponent(const IDetailLayoutBuilder& DetailBuilder);

	/** Gets the maximum based on the StatType (e.g., 100 for percentage-based; highest permanent for
	 *	current/permanent; etc.). */
	static float MaxStat(UStatsComponent* StatsComponent, const EStatValueType StatType, const bool bPercentage);

	/** Converts the value to FText depending on whether or not its an integer. */
	static FText FloatToFText(const float Value, const bool bIntegerOnly);

	/** Constructs a "stats widget" depending on the StatValueType (base stat, current/permanent, etc.). */
	void StatWidget(IDetailLayoutBuilder& DetailBuilder, FDetailWidgetRow& Widget, 
			const EStatEnum TargetStat, const EStatValueType StatValueType,
			const float OverallMaxValue, const bool bPercentage = false) const;

	/** Creates an "on reset" button delegate for a widget's OverrideResetToDefault (the button on the farthest right). */
	FSimpleDelegate CreateResetDelegate(IDetailLayoutBuilder& DetailBuilder, const EStatEnum TargetStat,
		const EStatValueType StatValueType, const float MaxStatValue) const;

#pragma endregion
	
};
