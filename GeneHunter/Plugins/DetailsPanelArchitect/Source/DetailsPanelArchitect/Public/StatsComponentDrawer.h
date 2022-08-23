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

	virtual void CustomizeBasePairsDetails(IDetailLayoutBuilder& DetailBuilder);

#pragma endregion

#pragma region Public utility functions

public:
	
	void SaveAndRefresh(IDetailLayoutBuilder& DetailBuilder) const;

	TFunction<void(const FText&, ETextCommit::Type&)> StatOnTextCommitted(
		IDetailLayoutBuilder& DetailBuilder, FStat& TargetStat,
		const EStatValueType StatValueType, const bool bPercentage) const;

	static bool UserCommitted(const ETextCommit::Type CommitType);

#pragma endregion

#pragma region Private utility functions
	
private:
	
	UStatsComponent* GetStatsComponent(const IDetailLayoutBuilder& DetailBuilder);

	static float MaxStat (const UStatsComponent* StatsComponent, const EStatValueType StatType, const bool bPercentage);
	
	static FText FloatToFText(const float Value, const bool bIntegerOnly);

	void StatWidget(IDetailLayoutBuilder& DetailBuilder, FDetailWidgetRow& Widget, 
			FStat& TargetStat, const EStatValueType StatValueType,
			const float OverallMaxValue, const bool bPercentage = false) const;

	FSimpleDelegate CreateResetDelegate(IDetailLayoutBuilder& DetailBuilder, FStat& TargetStat,
		const EStatValueType StatValueType, const float MaxStatValue) const;

#pragma endregion
	
};
