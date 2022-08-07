#pragma once
#include "DetailLayoutBuilder.h"
#include "PropertyEditor/Public/IDetailCustomization.h"
#include "StatsComponent.h"

class StatsComponentDrawer : public IDetailCustomization
{

#pragma region Variables

private:
	inline constexpr static float Padding = 2;
	inline constexpr static float StatInputWidth = 50;
	inline constexpr static float StatAbbrevMaxWidth = 30;
	inline constexpr static float ValueMaxWidth = 125;
	inline constexpr static float MaxHeight = 20;

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
	virtual void CustomizeLevelDetails(IDetailLayoutBuilder& DetailBuilder);

	virtual void CustomizeStatsDetails(IDetailLayoutBuilder& DetailBuilder);

#pragma endregion

#pragma region Private utility functions
	
private:
	
	UStatsComponent* GetStatsComponent(IDetailLayoutBuilder& DetailBuilder);

	void BuildStat(IDetailLayoutBuilder& DetailBuilder, TSharedPtr<IPropertyHandle> PropertyHandle,
		FStat& TargetStat, const EStatValueType StatValueType, const float MaxValue);

	static float MaxStat (const UStatsComponent* StatsComponent, const EStatValueType StatType, const bool bPercentage);

	static void SetStatFromString(FStat* Stat, const FText Text, const EStatValueType StatType);

#pragma endregion
	
};
