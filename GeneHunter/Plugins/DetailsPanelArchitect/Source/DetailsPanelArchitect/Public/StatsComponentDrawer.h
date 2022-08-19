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
	inline constexpr static float SlashWidth = 10;
	inline constexpr static float ValueMaxWidth = 125;
	inline constexpr static float MaxHeight = 20;
	inline constexpr static int SigFigs = 3;

	const FString LevelCategoryName = "Level";
	
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

	virtual void CustomizeExpDetails(IDetailLayoutBuilder& DetailBuilder);
	
	virtual void CustomizeCXPDetails(IDetailLayoutBuilder& DetailBuilder);

	virtual void CustomizeCurrentStatsDetails(IDetailLayoutBuilder& DetailBuilder);
	
	virtual void CustomizeBaseStatsDetails(IDetailLayoutBuilder& DetailBuilder);

#pragma endregion

#pragma region Private utility functions
	
private:
	
	UStatsComponent* GetStatsComponent(IDetailLayoutBuilder& DetailBuilder);

	static float MaxStat (const UStatsComponent* StatsComponent, const EStatValueType StatType, const bool bPercentage);

	static void SetStatFromString(FStat* Stat, const FText Text, const EStatValueType StatType);

	static bool UserCommitted(const ETextCommit::Type CommitType);

	static FText FloatToFText(const float Value, const bool bIntegerOnly);

	// Macro for stats (if not for GET_MEMBER_NAME_CHECKED, you could do this as a function
	#define CURRENT_STAT_PROPERTY(TargetStat, ValueMember, ValueMax, bPercentage) \
		const TSharedPtr<IPropertyHandle> Handle##TargetStat = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UStatsComponent, TargetStat)); \
		StatWidget(DetailBuilder, DetailBuilder.EditDefaultProperty( Handle##TargetStat )->CustomWidget(), StatsComponent->TargetStat, EStatValueType::Current, ValueMax, bPercentage);

	void StatWidget(IDetailLayoutBuilder& DetailBuilder, FDetailWidgetRow& Widget,
			FStat& TargetStat, const EStatValueType StatValueType, const float OverallMaxValue, const bool bPercentage = false);

#pragma endregion
	
};
